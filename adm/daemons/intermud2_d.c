/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : intermud2_d.c
 * Author : Cookys@RevivalWorld
 * Date   : 2001-01-22
 * Note   : 来和旧的 Intermud2 沟通的新版程式 , 改善原有 DNS_MASTER
 *	    有的 Bug , 大幅改写, 预计将以 intersys.c 整合之( I2, I3, 
 *          new protocol ).
 * Update :
 *  o 2001-01-22 Cookys 糟糕 , 好像不会有 DNS_FAKE 出现了噎 :Q
 *  o 2001-01-22 Cookys 自动加入达成条件的 mud 及删除三天没回应的mud
 *  o 2001-01-24 Cookys 降低进入 mudlist 标准, 并完成 mudlist a/q ,
 *			现在一虑不接受 mudlist 以外的任何 service
 *			request.(ping 除外) 
 *  o 2001-01-24 Cookys gwizmsg , warning , startup 完成
 *  o 2001-01-28 Cookys affirmation gtell support locate 完成
 *  o 2001-02-03 Cookys 解决 incoming_mudlist 造成无限回圈送ping问题
 *  o 2001-07-25 Cookys 增加讯息进入站内后的过滤[使用 ansi package]
 * 
 * 注意   : 为避免对自己 mud 无限送 ping 的情形，请在 OS 系统中的 /etc/hosts 做正确设定。
 *
 -----------------------------------------
 */

/*********************<   i2d.h     >*********************
#define MUD                     0
#define STREAM                  1
#define DATAGRAM                2
#define STREAM_BINARY           3
#define DATAGRAM_BINARY         4
//-----------------------------------------------
#define I2D_MUD_SERVER          ({"113.31.21.157", 5004})
#define MUDLIST_UPDATE_INTERVAL 600
#define REFRESH_INCOMING_TIME   3*60*60
//----------------------位元运算用-------------------------
#define GB_CODE                 1       // gb站点
#define ANTI_AD                 2       // 有垃圾广告的站点
#define IGNORED                 4       // 被本站屏蔽信息站点
#define SHUTDOWN                8       // 关闭的站点
#define ONLINE                  16      // 可连接站点
#define DISCONNECT              32      // 失去联系的站点
#define ENCODE_CONFIRM          64      // 系统自动判定gb/big5码的站点
***********************************************************/

#include <ansi.h>
#include <i2d.h>
#include <socket_err.h>
#include <origin.h>
#include <mudlib.h>
#include <message.h>


inherit F_DBASE;

#define NCH_CHANNEL(x) CHANNEL_D->channel_broadcast("nch", "I2D 精灵："+(string)x)

nosave string my_address;
nosave string localhost = "1270.0.01";      // mud的ip地址
nosave int udp_port = 6666;       // mud的udp端口

mapping mudlist=([]);
nosave mapping incoming_mudlist=([]);
string save_path = "/data/network/";

int udp_socket,refresh_limit=time(),debug;

// prototype
varargs string SAVE_PATH(string name,int flag);
varargs string *fetch_mudname(string arg,int flag);
string get_mud_name(mapping info);
int compare_mud_info(mapping info);

void receive_mudlist_request(mapping info);
void receive_mudlist_answer(mapping info);
void receive_ping_request(mapping info);
void receive_ping_answer(mapping info);
void receive_gchannel_msg(mapping info);
void receive_shutdown(mapping info);
void receive_gwiz_msg(mapping info);
void receive_warning(mapping info);
void receive_startup(mapping info);
void receive_gtell(mapping info);
void receive_affirmation(mapping info);
void receive_support_request(mapping info);
void receive_support_answer(mapping info);
void receive_locate_request(mapping info);
void receive_locate_answer(mapping info);
void receive_rwho_answer(mapping info);
void receive_rwho_request(mapping info);


void send_ping_request(string target, int port);
void send_mudlist_request(string target, int port);
void read_callback(int socket,string info,string address);
void send_shutdown(string target, int port);
void send_startup(string targ,int port);
varargs void send_warning(string targ,int port,string msg,string fakehost);
void refresh_ping_buffer();
void refresh_buffers();
protected void set_mudlist(string name,mapping info);
protected void set_incoming_mudlist(string name,mapping info);
protected void resolve_callback(string addr, string resolved, int key);

//-------------------------------------------------------------------------------------------
nosave mapping service_handler = ([
    "mudlist_q" :       (: receive_mudlist_request :),
    "mudlist_a" :       (: receive_mudlist_answer :),
    "ping_q" :          (: receive_ping_request :),
    "ping_a" :          (: receive_ping_answer :),
    "gchannel" :        (: receive_gchannel_msg :),
    "shutdown" :        (: receive_shutdown :),
    "gwizmsg" :         (: receive_gwiz_msg :),
    "warning" :         (: receive_warning :),
    "startup" :         (: receive_startup :),
    "gtell"     :       (: receive_gtell :),
    "affirmation_a":    (: receive_affirmation :),
    "support_q" :       (: receive_support_request :),
    "support_a" :       (: receive_support_answer :),
    "locate_q" :        (: receive_locate_request :),
    "locate_a" :        (: receive_locate_answer :),
    "rwho_a" :          (: receive_rwho_answer :),
    "rwho_q" :          (: receive_rwho_request :),

]);
nosave mapping ping_buffer=([]);
nosave mapping affirmation_buffer=([]);
nosave mapping rwho_buffer=([]);
nosave mapping gtell_buffer=([]);
nosave mapping msg_buffer=([]);
//-------------------------------------------------------------------------------------------

#define GTELL_B         1
#define PING_B          2
#define AFFIRMATION_B   3
#define RWHO_B          4

void restore()
{
        restore_object(SAVE_PATH("i2d"));
}

int save()
{
        return save_object(SAVE_PATH("i2d"));
}

// 将没 status  的全部设成 0
void make_status()
{
        foreach(string t , mapping ref d in mudlist)
        if(undefinedp(d["STATUS"])) d["STATUS"]=0;

        foreach(string t , mapping ref d in incoming_mudlist)
        if(undefinedp(d["STATUS"])) d["STATUS"]=0;
}

int check_dns_fake(string name)
{
        return sizeof(fetch_mudname(name))-1;
}

// 自动更新 incoming_mudlist 到 mudlist
void refresh_incoming()
{
        string name;
        mapping info;
        foreach(name , info in incoming_mudlist)
        if(info["CONNECTION"] > (REFRESH_INCOMING_TIME/MUDLIST_UPDATE_INTERVAL)-8 )
        {
                map_delete(info,"CONNECTION");
                mudlist[name]=info;
                map_delete(incoming_mudlist,name);
        }
        foreach( name,info in mudlist)
        if( info["HOSTADDRESS"]!=localhost && ((time()-info["LASTESTCONTACT"]> 259200) ||
                (time()-info["LASTESTCONTACT"]>5*60*60 && check_dns_fake(info["NAME"])>0 ) ))
                map_delete(mudlist,name);
        incoming_mudlist=([]);
        refresh_limit=time();
        save();
}

void delete_mudlist(string mud)
{
        map_delete(mudlist,mud);
        save();
}

void add_incoming_mudlist(string address, int port)
{
        send_ping_request(address, port);
        send_mudlist_request(address, port);
}

void send_all_shutdown()
{
        string mud;
        mapping info;
        // 取得 mudlist 所含的资讯
        if( mapp(mudlist) )
                foreach(mud, info in mudlist)
                send_shutdown(
                    info["HOSTADDRESS"],
                    info["PORTUDP"]
                );

        // 取得 incoming_mudlist 所含资讯
        if( mapp(incoming_mudlist) )
                foreach(mud, info in incoming_mudlist)
                send_shutdown(
                    info["HOSTADDRESS"],
                    info["PORTUDP"]
                );
}

/*
string start_message()
{
        return sprintf( "||MUDNAME:%s||NAME:%s||VERSION:%s||DRIVER:%s||MUDLIB:%s"
                "||HOST:%s||PORT:%d||PORTUDP:%d||TIME:%s||ENCODING:%s||USERS:%d||TCP:%s", 
                CHINESE_MUD_NAME,Mud_name(),MUDLIB_VERSION, __VERSION__, MUDLIB_NAME,
                query_host_name(),mud_port(), my_port, ctime(time()), MUDLIB_ENCODING,
                sizeof(users()), TCP_SERVICE_LEVEL);
}
*/

nosave mapping this_host = ([
        "NAME":         INTERMUD_MUD_NAME,      
        "MUDNAME":      CHINESE_MUD_NAME,
        "MUDGROUP":     MUD_GROUP,
        "HOST":         MUD_HOST_NAME,
        "HOSTADDRESS":  localhost,
        "LOCATION":     MUD_LOCATION,
        "DRIVER":       __VERSION__,
        "MUDLIB":       MUDLIB_NAME,
        "MUDTYPE":      MUD_TYPE,
        "VERSION":      MUDLIB_VERSION_NUMBER,
        "ENCODING":     MUD_ENCODING,
/*
        "STATUS":       ONLINE,
        "USERS":        ""+sizeof(users()),
*/
        "PORTUDP":      ""+fetch_variable("udp_port"),
        "PORT":         ""+__PORT__,
/*
        "TIME":         ""+uptime(),
*/
]);

// 定时更新 mud 资讯
//protected void update_info()
void update_info()
{
        string mud;
        mapping data,info;
        // 取得 mudlist 所含的资讯
        if( mapp(mudlist) )
                foreach(mud, info in mudlist)
                send_ping_request(
                    info["HOSTADDRESS"],
                    info["PORTUDP"]
                );
        // 取得 incoming_mudlist 所含资讯
        if( mapp(incoming_mudlist) )
                foreach(mud, info in incoming_mudlist)
                send_ping_request(
                    info["HOSTADDRESS"],
                    info["PORTUDP"]
                );
        refresh_buffers();
        // 在 REFRESH_INCOMING_TIME 所设的时间到自动加入符合条件的 mud
        if( time()- refresh_limit > REFRESH_INCOMING_TIME )
        {
                refresh_incoming();

                // 再次取得 incoming_mudlist
                foreach(string t, mapping d in mudlist)
                send_mudlist_request(d["HOSTADDRESS"],d["PORTUDP"]);
        }


        // 加入本mud进入mudlist
        data = this_host + ([ "LASTESTCONTACT"  : time(),
                              "STATUS"          : ONLINE,
                              "TIME"            : ""+uptime(),
                              "USERS"           : ""+sizeof(users()), ]);
                           
        mudlist[localhost+":"+udp_port] = data;
                
        // 定时 MUDLIST_UPDATE_INTERVAL 秒更新一次资讯
        //call_out((: update_info :),MUDLIST_UPDATE_INTERVAL);
        SCHEDULE_D->set_event(MUDLIST_UPDATE_INTERVAL, 1, this_object(), "update_info"); 
}

// 一开始从这被呼叫 , 这没问题吧 :Q
void create()
{
        seteuid(getuid());
        // 取回 save 下来的资料
        restore();
        resolve( query_host_name(), (: resolve_callback :) );
        // 初始化 UDP port
        if( (udp_socket = socket_create(DATAGRAM, (: read_callback :) )) < 0 )
        {
                NCH_CHANNEL("UDP socket created fail.\n");
                error("Unable to create UDP socket.\n");
        }
        while( EEADDRINUSE==socket_bind(udp_socket, udp_port) )
                udp_port++;

        NCH_CHANNEL("初始化完成 , 使用 UDP port: "+udp_port);
                
        refresh_buffers();
        // 呼叫定时更新的函式
        refresh_ping_buffer();
        
        // 送出 startup
        foreach(string mud,mapping info in mudlist)
        {
                mudlist[mud]["STATUS"]&=~ENCODE_CONFIRM;
                send_startup(info["HOSTADDRESS"],info["PORTUDP"]);
        }

        // 送出 ping 要求给 server
        //send_ping_request(I2D_MUD_SERVER[0],I2D_MUD_SERVER[1]);
        // 向预设 server 取得 mudlist
        //send_mudlist_request(I2D_MUD_SERVER[0],I2D_MUD_SERVER[1]);
        // 先抓一次 incoming_mudlist
        foreach(string t, mapping d in mudlist)
        send_mudlist_request(d["HOSTADDRESS"],d["PORTUDP"]);
        // 开始定期更新资讯
        evaluate((: update_info :));
}

// destruct 的 simul_efun 会先 call 这个
int remove()
{
        send_all_shutdown();
        socket_close(udp_socket);
        return save();
}

public void mud_shutdown()
{
        send_all_shutdown();
        socket_close(udp_socket);
        save();
}

protected void resolve_callback(string addr, string resolved, int key)
{
        my_address = resolved;
}

// UDP port 收进来的东西会先经过这
protected void read_callback(int socket,string info,string address)
{
        string *infoclip,title,datas;
        mixed handler;
        mapping infomap=([]);

#ifdef __PACKAGE_ANSI__
        info=ansi(info);
#endif
        //if( debug) NCH_CHANNEL( sprintf( "socket %d\ninfo %s\naddress %s", socket, info, address ));
        // 检查封包格式是否正确
        if(!sscanf(info,"@@@%s@@@%*s",info)) return;
        // 近一步到专属的 service 分析
        infoclip = explode(info,"||");
        // 本站无法处理的服务在这过滤
        if(!infoclip || undefinedp(handler = service_handler[infoclip[0]]) )
        {
                NCH_CHANNEL(sprintf("Unknow I2 service %s from %s ",infoclip[0],address));
                return;
        }
        // 将 string -> mapping 以便往下传递
        foreach(string data in infoclip)
        if( sscanf(data, "%s:%s", title, datas)==2 ) infomap[title] = datas;
        // 将发送此 package 的 IP 纪录到 mapping info 中
        sscanf(address, "%s %*s", address);
        if( (address+"" == my_address || address+"" == localhost)&& infomap["PORTUDP"]==udp_port+"" )
                return;
        infomap["HOSTADDRESS"] = address;
        if(debug) NCH_CHANNEL(sprintf("收到%s\n%O\n",address,info));
        // 交付给 service 专用的 function
        //call_other(this_object(),handler,infomap);
        evaluate(handler,infomap);

}

// 送出讯息用的函式
void send_udp(string targ, mixed port, string service, mapping info)
{
        int socket;
        string title,data,msg;
        string mudname;

        // 不传送我们没有的服务
        if( undefinedp(service_handler[service]) )
        {
                NCH_CHANNEL("Unknow Service.");
                error("Invalid intermud Services.\n");
        }

        // 不传送资料给自己.
        //NCH_CHANNEL(sprintf("ip:%s port:%s services:%s",targ,port,service));
        //NCH_CHANNEL(sprintf("%O",typeof(port)));
        if( (targ == my_address || targ == localhost) && port == udp_port )
                //if( service!="ping_a" && service!="ping_q" )
                return;


        // 建立 socket 以开始传送
        socket = socket_create(DATAGRAM, "read_callback");
        if( !socket ) return;

        // 将 mapping -> string
        msg = service;
        if( mapp(info) ) {
                foreach(title, data in info) {
                        if( !stringp(title) || !stringp(data) ) continue;
                        msg += sprintf("||%s:%s",title,data);
                }
        }
        mudname = targ+":"+port;
        /*
        if( !undefinedp(mudlist[mudname]) && ( (mudlist[mudname]["STATUS"]& GB_CODE) || ( !undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="gb") ))
                //if( (mudlist[mudname]["STATUS"]& GB_CODE) || ( !undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="gb") )
                msg = (string)LANGUAGE_D->toGB(msg); 
        */
        if( !undefinedp(mudlist[mudname]) && ( /*!(mudlist[mudname]["STATUS"]& GB_CODE) ||*/ ( !undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="big5") ))
                msg = (string)LANGUAGE_D->toBig5(msg);  // 转换成big5码发出信息
                
        // 送出讯息.
        socket_write(socket, "@@@" + msg + "@@@", targ + " " + port);
        // debug msg
        if(debug) NCH_CHANNEL(sprintf("送出到%s:\n%s\n"+HIY+"%O\n"+NOR,targ,port+"",msg));
        // 关闭传送完毕的 socket
        socket_close(socket);


}
// 由 mapping package 中取得 mud name
string get_mud_name(mapping info)
{
        return info["HOSTADDRESS"]+":"+info["PORTUDP"];
}

// 由 mud name 辨认为第几级资料
int get_info_level(string mudname)
{
        if( member_array(mudname,keys(mudlist))==-1)
        {
                if(member_array(mudname,keys(incoming_mudlist))==-1)
                        return -1;
                else    return 0;
        }
        else return 1;
}

void analyze_mud_info(mapping info)
{
        int info_level=get_info_level(get_mud_name(info));

        switch(info_level) {
        case -1: set_incoming_mudlist(get_mud_name(info),info);break;
        case  0: set_incoming_mudlist(get_mud_name(info),info);break;
        case  1: set_mudlist(get_mud_name(info),info);break;
        }
}
// 用于大部分函式, 分析 Mud 是否为已通过认证, 尚未认证送 pin_q
int compare_mud_info(mapping info)
{
        string mudname=get_mud_name(info);
        int level=get_info_level(mudname);

        if( level < 1 )
                send_ping_request(info["HOSTADDRESS"],info["PORTUDP"]);
        else if( mudlist[mudname]["STATUS"] &(SHUTDOWN | DISCONNECT))
        {
                mudlist[mudname]["STATUS"]&=(~(SHUTDOWN | DISCONNECT));
                mudlist[mudname]["STATUS"]|=ONLINE;
        }
        return level;
}

// 设定 or 更新 mudlist 资讯
protected void set_mudlist(string name,mapping info)
{
        mapping map;
        string t,d;

        // 用 IPADDRESS:PORT 做 index , 防止 fake , 若资料不合则挡掉
        if( sscanf(name, "%*d.%*d.%*d.%*d:%*d") != 5 ) return;
        // 还没有此间 mud 资料? 添加进mudlist
        if( undefinedp(map = mudlist[name]) )
        {
                // 给定 mudname
                mudlist[name] = info;
                // 初始化 mud STATUS
                mudlist[name]["STATUS"]=0;
                return;
        }

        // 已存在资料,更新资讯 ...
        foreach(t, d in info) mudlist[name][t]=d;

}
// 设定 or 更新 incoming mudlist 资讯
protected void set_incoming_mudlist(string name,mapping info)
{
        mapping map;
        string t,d;

        if( sscanf(name, "%*d.%*d.%*d.%*d:%*d") != 5 ) return;
        if( undefinedp(map = incoming_mudlist[name]) )
        {
                incoming_mudlist[name] = info;
                incoming_mudlist[name]["CONNECTION"]=1;
                return;
        }

        // 更新资讯
        foreach(t, d in info) incoming_mudlist[name][t]=d;
        // 每次更新资讯连线回应计算 + 1
        incoming_mudlist[name]["CONNECTION"]+=1;
}

// 清除暂存区
void refresh_buffers()
{
        rwho_buffer=([]);
        gtell_buffer=([]);
        affirmation_buffer=([]);
        //refresh_ping_buffer();
        msg_buffer=([]);
}

/********************************************************************************************
 * 由外界能设定内部状况的沟通函式..                                                         *
 ********************************************************************************************/

// SAVE_PATH 若传入 flag , 即用以更新 SAVE_PATH
varargs string SAVE_PATH(string name,int flag)
{
        if(!flag) return save_path+name;
        else
        {
                save_path = name;
                save();
                return "SAVE_PATH "+save_path+" updated successfully.\n";
        }
}

void debug()
{
        if( !debug ) debug = 1;
        else debug = 0;
}

//--------------------------------------------------------------------------------------------
// Status 系列
//--------------------------------------------------------------------------------------------

// 用"ip:port"来寻找 mud data
mixed fetch_data(string name)
{
        int level;
        level = get_info_level(name);
        switch(level){
        case -1: return 0;
        case 1: return mudlist[name];
        case 0: return incoming_mudlist[name];
        }
        return 0;
}

// 用英文名寻找登记名 , 传回符合的阵列
varargs string *fetch_mudname(string arg,int flag)
{
        mapping info;
        string name,*result=({});
        if( flag ) arg=lower_case(arg);
        foreach(name , info in (mudlist+incoming_mudlist))
        if(!flag)
        {
                if( arg==info["NAME"] )
                        result+=({name});
        }
        else    if( strsrch(lower_case(info["NAME"]),arg)!=-1 )
                result+=({name});
        return result;
}
// 用 mud ip 来寻找登记名 , 传回符合阵列
varargs string *fetch_mudip(string arg)
{
        mapping info;
        string name,*result=({}),ip;
        //if( flag ) arg=lower_case(arg);
        foreach(name , info in (mudlist+incoming_mudlist))
        {
                sscanf(name,"%s:%*s",ip);
                if( arg == ip )
                        result+=({name});
        }
        return result;
}

// 设定 mudlist 里的 mud 设定
int set_status(string mud,int num)
{
        int level;
        level = get_info_level(mud);
        if(level!=1 ) return 0;

        if( num > 0)
        {
                // 已经有此项设定
                if(mudlist[mud]["STATUS"] & num)
                        return 0;
                else mudlist[mud]["STATUS"]+=num;
        }
        else
        {       // 已经有此项设定
                if(!mudlist[mud]["STATUS"]&num)
                        return 0;
                else mudlist[mud]["STATUS"]-=(-num);
        }
        NCH_CHANNEL(sprintf("%s (%s) 加入属性 [%d]",mudlist[mud]["NAME"],mud,num));
        save();
        return 1;
}

void add_buffer(string mudname,int kind)
{
        //if(get_info_level(mudname)<1)
        //      return;
        switch(kind)
        {
        case GTELL_B:
                if(undefinedp(gtell_buffer[mudname]))
                        gtell_buffer[mudname]=1;
                else
                        gtell_buffer[mudname]++;
                break;
        case PING_B:
                if(undefinedp(ping_buffer[mudname]))
                        ping_buffer[mudname]=({1,time()});
                else
                {
                        ping_buffer[mudname][0]++;
                        ping_buffer[mudname][1]=time();
                }
                break;
        case RWHO_B:
                if(undefinedp(rwho_buffer[mudname]))
                        rwho_buffer[mudname]=1;
                else
                        rwho_buffer[mudname]++;
                break;
        case AFFIRMATION_B:
                if(undefinedp(affirmation_buffer[mudname]))
                        affirmation_buffer[mudname]=1;
                else
                        affirmation_buffer[mudname]++;
        }
}

void sub_buffer(string mudname,int kind)
{
        //if(get_info_level(mudname)<1)
        //      return;
        switch(kind)
        {
        case GTELL_B:
                if(undefinedp(gtell_buffer[mudname]))
                        return;
                else
                {
                        gtell_buffer[mudname]--;
                        if(gtell_buffer[mudname]<1)
                                map_delete(gtell_buffer,mudname);
                }

                break;
        case PING_B:
                if(undefinedp(ping_buffer[mudname]))
                        return;
                else
                {
                        ping_buffer[mudname][0]--;
                        if( ping_buffer[mudname][0] < 1)
                                map_delete(ping_buffer,mudname);
                }
                break;
        case RWHO_B:
                if(undefinedp(rwho_buffer[mudname]))
                        return;
                else
                {
                        rwho_buffer[mudname]--;
                        if( rwho_buffer[mudname] < 1)
                                map_delete(ping_buffer,mudname);
                }
                break;
        case AFFIRMATION_B:
                if(undefinedp(affirmation_buffer[mudname]))
                        return;
                else
                {
                        affirmation_buffer[mudname]--;
                        if(affirmation_buffer[mudname]<1)
                                map_delete(affirmation_buffer,mudname);
                }
        }
}

int test_buffer(string mudname,int kind)
{
        switch(kind){
        case GTELL_B:
                if( !undefinedp(gtell_buffer[mudname]) ) return 1;
                break;
        case PING_B:
                if( !undefinedp(ping_buffer[mudname]) ) return 1;
                break;
        case RWHO_B:
                if( !undefinedp(rwho_buffer[mudname]) ) return 1;
                break;
        case AFFIRMATION_B:
                if( !undefinedp(affirmation_buffer[mudname]) ) return 1;
                break;
        }
        return 0;
}
/********************************************************************************************
 * 由此处开始 , 以下均为各种服务类别                                                        *
 ********************************************************************************************/

//--------------------------------------------------------------------------------------------
// Ping 系列
//--------------------------------------------------------------------------------------------
/* Intermud2 ping_q 封包格式
        ([
                "NAME":         (string)这 Mud 的网路名称[慎选]
                                旧的 DNS_MASTER 如果遇到相同会 DNS_FAKE.
                "PORTUDP":      (int)(到最后都会被包成string)
                                这个mud的intermud2 daemon 监听的 udp port.
        ])

    Intermud2 ping_a 封包格式
        ([
                "NAME":         (string)这 Mud 的网路名称
                "MUDGROUP":     (string)网路群组?
                "HOST":         (string)Mud 主机名称?(好像没用, 花瓶一个)
                "LOCATION":     (string)所在地?
                "MUDLIB":       (string)mudlib, 如果不是Eastern Stories会收不到 es channel.
                "VERSION":      (string)mudlib 版本?
                "ENCODING":     (string)编码方式有 BIG5/GB,
                "USERS":        (int) users
                "PORTUDP":      (int) UDP port,
                "TIME":         (int) uptime,
        ])
*/


// ping_buffer 用来挡掉不必要的 ping request
// 避免被 save 浪费资源宣成 nosave


// 发出 Ping 要求
void send_ping_request(string target, int port)
{
        send_udp(target, port, "ping_q", ([
                "NAME":         INTERMUD_MUD_NAME,
                "PORTUDP":      ""+udp_port,
            ]));
        //if(get_info_level(target+":"+port)>0)
        add_buffer(target+":"+port,PING_B);
        if(debug) NCH_CHANNEL("送出 PING 要求到 " + target + ":" + port + "。");
}

void refresh_ping_buffer()
{
        string t;
        int *d;
        // 再次执行此函式时不要有 callout 还在跑
        remove_call_out("refresh_ping_buffer");

        foreach(t,d in ping_buffer)
        if(time()-d[1] > 90)
        {
                int flag;
                //NCH_CHANNEL("peer...."+sprintf("%O%O\n",t,mudlist[t]["STATUS"]));
                if( get_info_level(t)==1 && !(mudlist[t]["STATUS"]&SHUTDOWN))
                {

                        mudlist[t]["STATUS"]&=(~ONLINE);
                        mudlist[t]["STATUS"]|=DISCONNECT;

                        // 2 hr内不见的站一直 ping -.-
                        if( time() - mudlist[t]["LASTESTCONTACT"] < 60*60*2 )
                                flag=1;
                }
                map_delete(ping_buffer,t);
                if( flag )
                {
                        send_ping_request(mudlist[t]["HOSTADDRESS"],mudlist[t]["PORTUDP"]);
                        flag=0;
                }
        }
        call_out("refresh_ping_buffer",60);
}

// 收到 ping request
void receive_ping_request(mapping info)
{
        int port;

        // UDP_PORT 格式错误
        if( undefinedp(info["PORTUDP"]) || !sscanf(info["PORTUDP"],"%d",port) ) return;
        
        if( (info["HOSTADDRESS"]==my_address || info["HOSTADDRESS"]==localhost) && port == udp_port )
                return;
        // 如果我们 mudlist 里还没有此 mud , 我们也要求他回 ping.
        if(get_info_level(get_mud_name(info))<0)
                compare_mud_info(info); // 发送ping要求
        // 送出 PING Answer
        send_udp(info["HOSTADDRESS"], port, "ping_a",
            ([
                "NAME":         INTERMUD_MUD_NAME,      // mudlib.h 中定义
                "MUDNAME":      CHINESE_MUD_NAME,
                "MUDGROUP":     MUD_GROUP,
                "HOST":         MUD_HOST_NAME,
                "LOCATION":     MUD_LOCATION,
                "DRIVER":       __VERSION__,
                "MUDLIB":       MUDLIB_NAME,
                "VERSION":      MUDLIB_VERSION_NUMBER,
                "ENCODING":     MUD_ENCODING,
                "USERS":        ""+sizeof(users()),
                "PORTUDP":      ""+udp_port,
                "PORT":         ""+__PORT__,
                "TIME":         ""+uptime(),
            ]));

        if(debug) NCH_CHANNEL("收到 PING 要求 , 送出回应到 "+info["HOSTADDRESS"]+":"+port+" .");
}

// 收到 PING 回应
void receive_ping_answer(mapping info)
{
        int status;
        
        string mudname=get_mud_name(info);
        // 有要求对方回 ping 吗?
        if( !test_buffer(mudname,PING_B) )
        {
                //if( !sscanf(info["PORTUDP"],"%*d") ) return;
                NCH_CHANNEL("收到不明 Ping Answer From: "+info["HOSTADDRESS"]+":"+info["PORTUDP"]+" [ "+info["NAME"]+" ] ");
                                
                if(get_info_level(mudname)<1)
                        receive_ping_request(info); // 发送ping

                send_warning(info["HOSTADDRESS"],info["PORTUDP"],"\aWe didn't ask for this ping request.","Sorry,");
                //compare_mud_info(info);
                // 去掉return,+add_buff, by Lonely
                add_buffer(mudname,PING_B);
                //return;
        }
        //if(get_info_level(mudname)>0)
        sub_buffer(mudname,PING_B);
        info["LASTESTCONTACT"]=time();
        analyze_mud_info(info);
        if( get_info_level(mudname) == 1)
        {
                if( mudlist[mudname]["STATUS"] &(SHUTDOWN | DISCONNECT))
                        mudlist[mudname]["STATUS"]&=(~(SHUTDOWN | DISCONNECT));
                mudlist[mudname]["STATUS"]|=ONLINE;
        }
        if(debug) NCH_CHANNEL("收到 "+info["HOSTADDRESS"]+" 送回的 PING ANSWER .");
}

//--------------------------------------------------------------------------------------------
// Mudlist 系列
//--------------------------------------------------------------------------------------------


// 送出 Mudlist 讯息专用的函式 -.-
void send_mudlist_udp(string targ, int port,string info)
{
        int socket;

        // 不传送资料给自己.
        if( (targ == my_address || targ == localhost) && port == udp_port ) return;

        // 建立 socket 以开始传送
        socket = socket_create(DATAGRAM, "read_callback");
        if( !socket ) return;

        // 送出讯息.
        socket_write(socket, "@@@mudlist_a||" + info + "@@@\n", targ + " " + port);
        // 关闭传送完毕的 socket
        socket_close(socket);
}

// 收到对方回应的 mudlist 列表
void receive_mudlist_answer(mapping info)
{
        string name,clip;

        foreach(name,clip in info)
        {
                string *prop_list;
                mapping mudinfo=([]);
                if( strsrch(clip,"NAME")==-1 ) continue;

                prop_list=explode(clip,"|")-({""});
                foreach(string prop in prop_list) {
                        string t, d;
                        if( sscanf(prop, "%s:%s", t, d)==2 ) mudinfo[t] = d;
                }
                // 收到没在清单上的 mud 就送 ping 要求
		// if(mudinfo["HOSTADDRESS"]!=my_address && mudinfo["HOSTADDRESS"]!=localhost)
                if( get_info_level(get_mud_name(mudinfo))<1 )
                        compare_mud_info(mudinfo); // 发送ping
        }

        if(debug) NCH_CHANNEL("收到 "+info["HOSTADDRESS"]+" 送回的 Mudlist Answer.");
}

// 要求对方发送 mudlist 列表
void send_mudlist_request(string targ, int port)
{
        send_udp(targ, port, "mudlist_q", ([
                "NAME":INTERMUD_MUD_NAME,
                "HOSTADDRESS":  localhost,
                "PORTUDP":      "" + udp_port,
            ]));
}

// 收到要求并送出 mudlist 列表
void receive_mudlist_request(mapping info)
{
        string name;
        mapping mudinfo;
        int i=1;
        if(!info["PORTUDP"]) return;
        if(get_info_level(get_mud_name(info))<1) return;

        foreach(name,mudinfo in mudlist)
        {
                // 没有即时回应的就有可能不在, 不送出以免制造网路垃圾
                if(!(mudinfo["STATUS"]&ONLINE)) continue;
                i++;
                send_mudlist_udp(info["HOSTADDRESS"],info["PORTUDP"],
                    sprintf("%d:|NAME:%s|HOST:%s|HOSTADDRESS:%s|PORT:%s|PORTUDP:%s|USERS:%s|TIME:%s",
                                i,mudinfo["NAME"],mudinfo["HOST"],mudinfo["HOSTADDRESS"],mudinfo["PORT"],mudinfo["PORTUDP"],mudinfo["USERS"],mudinfo["TIME"])

                );
        }
        if(debug) NCH_CHANNEL("收到 "+info["HOSTADDRESS"]+":"+info["PORTUDP"]+" 的 Mudlist Request 并回应之.");
}

//--------------------------------------------------------------------------------------------
// Shutdown 系列
//--------------------------------------------------------------------------------------------

void send_shutdown(string target, int port)
{
        send_udp(target, port, "shutdown",
            ([
                "NAME":INTERMUD_MUD_NAME,
                "PORTUDP":""+udp_port,
            ]));

        NCH_CHANNEL("送出 Shutdown 讯息到 " + target + ":" + port + "。");
}

void receive_shutdown(mapping info)
{
        if( compare_mud_info(info)==1 )
        {
                string name=get_mud_name(info);

                mudlist[name]["STATUS"]&=(~(ONLINE|DISCONNECT));
                mudlist[name]["STATUS"]|=SHUTDOWN;
        }
        NCH_CHANNEL("收到自 "+info["HOSTADDRESS"]+":"+info["PORTUDP"]+" 来的 Shutdown 讯息.");
}

//--------------------------------------------------------------------------------------------
// Gchannel 系列
//--------------------------------------------------------------------------------------------


void compare_last_msg(string mudname,string last_msg,string sender)
{
        if( undefinedp(msg_buffer[mudname]) || (msg_buffer[mudname][0]!=last_msg && msg_buffer[mudname][3]!=sender ))
        {
                //if( undefinedp(msg_buffer[mudname]) || msg_buffer[mudname][2] >= time()+15 )
                msg_buffer[mudname]=({ last_msg,1,time(),sender });

        }       else {
                if(msg_buffer[mudname][0]==last_msg || msg_buffer[mudname][3]==sender)
                        msg_buffer[mudname][1]++;
                msg_buffer[mudname][2]=time();
                msg_buffer[mudname][3]=sender;
        }

        if( msg_buffer[mudname][1] > 100 )
        {
                set_status(mudname,ANTI_AD);
                NCH_CHANNEL("将[ " + fetch_data(mudname)["MUDNAME"] +"] 加入 ANTI_AD 名单。");
        }
}

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}

int accept_channel(string channel)
{
        class channel_class ch;
        //mapping channels = load_object(CHANNEL_D)->query_chann();
        mapping channels=fetch_variable("channels",load_object(CHANNEL_D));

        if( !undefinedp(channels[channel]) && !undefinedp((ch=channels[channel])->extra["intermud"]) )
                return 1;
}

// 收到 gchannel 讯息
void receive_gchannel_msg(mapping info)
{
        string msg,id,mudname,str;
        int status;

        // 一定必须要有的栏位
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["USRNAME"])
            ||  undefinedp(info["CHANNEL"])
            ||  undefinedp(msg = info["MSG"])
        )   return;
        // 去除最后一个 \n
        if(msg[<1..<0] == "\n") msg[<1..<0] = "";
        // 新来的站给我乖乖排队回 ping :Q
        if( compare_mud_info(info)<1 ) return;

        mudname = get_mud_name(info);
        // 设定 id
        //id = info["USRNAME"] + "@"+ ((mudlist[mudname=get_mud_name(info)]["MUDNAME"])||"")+HBGRN"-"+mudlist[mudname]["NAME"]+"-"NOR;
        id = info["USRNAME"];
        // 有无中文 name ?
        if( info["CNAME"] ) id = info["CNAME"] + "(" + id + ")";
        // 是否为 Emote ?
        if( !undefinedp(info["EMOTE"]) )
                set("channel_id", id);

        mudname = get_mud_name(info);
        status = fetch_data(get_mud_name(info))["STATUS"];
        
        // 系统自动识别gb/big5码站点
        if( !(status & ENCODE_CONFIRM) && strlen(msg) > 20 )
        {
                string mud_ip_port = info["HOSTADDRESS"]+":"+info["PORTUDP"];
                int con = LANGUAGE_D->encode_conjecture(msg);

                if( con >= 0 && con <= 15 ) mudlist[mud_ip_port]["STATUS"]|=GB_CODE;
                else if( con > 30 ) mudlist[mud_ip_port]["STATUS"]&=~GB_CODE;

                if( con != -1 ) mudlist[mud_ip_port]["STATUS"]|=ENCODE_CONFIRM;
        }

        if( status & IGNORED )  // 如果被列入隔绝信息站点，则屏蔽网际聊天频道
        {
                if( info["EMOTE"] ) delete("channel_id");
                return;
        }

        if( !(status & GB_CODE) && ((status & ENCODE_CONFIRM) || (!undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="big5")) )

        {
                //id  = (string)LANGUAGE_D->toGB(msg);;
                msg = (string)LANGUAGE_D->toGB(msg);
        }

        if( status & ANTI_AD ) info["CHANNEL"]="ad";
        if( info["CHANNEL"]!="ad" )
        compare_last_msg(mudname,info["MSG"],id);
                               
        // 交付给 CHANNEL_D 处理
        // 作为其他非NTlib的mud，可直接用CHANNEL_D->do_channel(this_object(), info["CHANNEL"], msg, info["EMOTE"]);替换以下的内容
        //if( !(status & ANTI_AD) && accept_channel(info["CHANNEL"]) )
        if( accept_channel(info["CHANNEL"]) || info["CHANNEL"] == "ad") // 本站CHANNEL_D拥有这个频道或广告频道
        {
                str = (info["EMOTE"]?("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ msg): ("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ id+"："+msg));
                CHANNEL_D->channel_broadcast(info["CHANNEL"], str);
        }
        else // 放到其他other频道显示
        {
                str = (info["EMOTE"]?("["+info["CHANNEL"]+"] "+"{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+msg):("["+info["CHANNEL"]+"] {"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+id+"："+msg));
                CHANNEL_D->channel_broadcast("other", str);
        }
        if( info["EMOTE"] ) delete("channel_id");
}

// 发出 gchannel 讯息
void send_gchannel_msg(string channel, string id, string name, string msg, int emoted)
{
        mapping info,mudinfo;
        string t;

        if(msg[<1..<0] == "\n") msg[<1..<0] = "";

        msg = replace_string(msg, "|", "|\033[1m");
        msg = replace_string(msg, "@", "@\033[1m");
        info = ([
            "NAME":         INTERMUD_MUD_NAME,
            "PORTUDP":      "" + udp_port,
            "USRNAME":      id,
            "CNAME":        name,
            "CHANNEL":      channel,
            "ENCODING":     MUD_ENCODING,
            "MSG":          msg
        ]);


        if( emoted ) info["EMOTE"] = "YES";

        foreach(t, mudinfo in (mudlist+incoming_mudlist))
        send_udp(mudinfo["HOSTADDRESS"], mudinfo["PORTUDP"],"gchannel", info);
}


//--------------------------------------------------------------------------------------------
// Gwizmsg 系列
//--------------------------------------------------------------------------------------------

/*
info = ([
                "NAME" : INTERMUD_MUD_NAME,
                "PORTUDP" : "" + fetch_variable("udp_port"),
                "WIZNAME" : id,
                "CNAME" : name,
                "CHANNEL" : ch,
                "ENCODING" : CHARACTER_SET,
                "GWIZ" : msg,
        ]);

*/
void receive_gwiz_msg(mapping info)
{
        string msg,id,mudname;
        int status;

        // 一定必须要有的栏位
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["WIZNAME"])
            ||  undefinedp(info["CHANNEL"])
            ||  undefinedp(msg = info["GWIZ"])
        )   return;
        // 去除最后一个 \n
        if(msg[<1..<0] == "\n") msg[<1..<0] = "";
        // 新来的站给我乖乖排队回 ping :Q
        if( compare_mud_info(info)<1 ) return;

        // 设定 id
        id = info["WIZNAME"];
        //id = info["WIZNAME"] + "@" + info["NAME"];
        // 有无中文 name ?
        if( info["CNAME"] ) id = info["CNAME"] + "(" + id + ")";
        
        // 是否为 Emote ?
        if( !undefinedp(info["EMOTE"]) )
                set("channel_id", id);
        // GB 转码 ?
        mudname=get_mud_name(info);

        status = fetch_data(mudname)["STATUS"];

        if( !(status & ENCODE_CONFIRM) && strlen(msg) > 20 )
        {
                string mud_ip_port = info["HOSTADDRESS"]+":"+info["PORTUDP"];
                int con = LANGUAGE_D->encode_conjecture(msg);

                if( con >= 0 && con <= 15 ) mudlist[mud_ip_port]["STATUS"]|=GB_CODE;
                else if( con > 30 ) mudlist[mud_ip_port]["STATUS"]&=~GB_CODE;

                if( con != -1 ) mudlist[mud_ip_port]["STATUS"]|=ENCODE_CONFIRM;
        }

        /*
        if( status & IGNORED ) // 如果被列入隔绝信息站点，则屏蔽网际聊天频道
        {
                if( info["EMOTE"] ) delete("channel_id");
                return;
        }
        */

        if( !(status & GB_CODE) && ((status & ENCODE_CONFIRM) || (!undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="big5")) )
        {
                // id = (string)LANGUAGE_D->toGB(id);
                msg = (string)LANGUAGE_D->toGB(msg);
        }
        
        // 作为其他非NTlib的mud，可直接用CHANNEL_D->do_channel(this_object(), info["CHANNEL"], msg, info["EMOTE"]);替换以下的内容
        if( status & ANTI_AD ) // 垃圾广告站点
        {
                info["CHANNEL"]="ad"; // 把对方网络频道改成广告频道
                CHANNEL_D->channel_broadcast(info["CHANNEL"], info["EMOTE"]?("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ msg):("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ id+"："+msg));

                if( info["EMOTE"] ) delete("channel_id");
                return;
        }

        // 交付给 CHANNEL_D 处理
        CHANNEL_D->channel_broadcast("gwiz","["+info["CHANNEL"]+"] "+(info["EMOTE"]?("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+msg):("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ id+"："+msg)));
        if( info["EMOTE"] ) delete("channel_id");

        //NCH_CHANNEL("收到 gwizmsg "+info["CHANNEL"]+" 讯息");
}
void send_gwiz_msg(string channel, string id, string name, string msg, int emoted)
{
        mapping info,mudinfo;
        string t;

        if(msg[<1..<0] == "\n") msg[<1..<0] = "";
        msg = replace_string(msg, "|", "|\033[1m");
        msg = replace_string(msg, "@", "@\033[1m");
        info = ([
            "NAME":         INTERMUD_MUD_NAME,
            "PORTUDP":      "" + udp_port,
            "WIZNAME":      id,
            "CNAME":        name,
            "CHANNEL":      channel,
            "ENCODING":     MUD_ENCODING,
            "GWIZ":          msg,
        ]);
        if( emoted ) info["EMOTE"] = "YES";

        foreach(t, mudinfo in (mudlist+incoming_mudlist))
        send_udp(mudinfo["HOSTADDRESS"], mudinfo["PORTUDP"],"gwizmsg", info);
}

//--------------------------------------------------------------------------------------------
// Warning 系列
//--------------------------------------------------------------------------------------------

void receive_warning(mapping info)
{
        string msg;

        if(compare_mud_info(info)<1)
                return;

        msg=sprintf("自 %s(%s) 告知的警告: %s 于 %s",info["NAME"],info["HOSTADDRESS"],info["MSG"],info["FAKEHOST"]);

        send_warning(info["HOSTADDRESS"],info["PORTUDP"],
            sprintf("Thank For Your Warning [%s], we have loged it , and will try to solve it soon :).",msg));

        //log_file("static/intermud2", "[warn]"+msg);
        NCH_CHANNEL(msg);
}

varargs void send_warning(string targ,int port,string msg,string fakehost)
{
        send_udp(targ, port, "warning",
            ([
                "NAME":INTERMUD_MUD_NAME,
                "PORTUDP":""+udp_port,
                "MSG":msg,
                "FAKEHOST":fakehost?fakehost:"",
            ]));

}

//--------------------------------------------------------------------------------------------
// Startup 系列
//--------------------------------------------------------------------------------------------

// 送出 startup ,  反正马上就送 ping 了, 送基本的就好.
void send_startup(string targ,int port)
{
        send_udp(targ, port, "startup",
            ([
                "NAME":INTERMUD_MUD_NAME,
                "PORTUDP":""+udp_port,
            ]));
        // 对方收到 startup 会回 ping_a
        add_buffer(targ+":"+port,PING_B);
        //NCH_CHANNEL("送出 startup 讯息到 " + targ + ":" + port + "。");
}

void receive_startup(mapping info)
{
        receive_ping_request(info);
        NCH_CHANNEL("收到自 "+info["HOSTADDRESS"]+":"+info["PORTUDP"]+" 来的 startup 讯息.");
}

//--------------------------------------------------------------------------------------------
// affirmation_a 系列
//--------------------------------------------------------------------------------------------


void add_affirmation_buffer(mapping info,string service)
{
        string name=get_mud_name(info);

        service=lower_case(service);

        if(!undefinedp(affirmation_buffer[name+"-"+service]) )
                affirmation_buffer[name+"-"+service]++;
        else affirmation_buffer[name+"-"+service]=1;
}

void receive_affirmation(mapping info)
{
        string name=get_mud_name(info);
        object ob;

        if(compare_mud_info(info)<1)
                return;
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["WIZTO"])
            ||  undefinedp(info["MSG"])
            ||  undefinedp(info["MSG"])
        )   return;

        if( undefinedp(affirmation_buffer[name+"-"+info["TYPE"]]))
        {

                send_warning(info["HOSTADDRESS"],info["PORTUDP"],
                    "Affirmation warning : Your mud send unrequest Affirmation_a Please improve it.");
                NCH_CHANNEL(sprintf("Unrequest affirmation answer from %s:%s(%s)   \n%O\n",info["HOSTADDRESS"],info["PORTUDP"]+"",info["NAME"],info));
                return ;

        }
        affirmation_buffer[name+"-"+info["TYPE"]]--;
        if( !ob=find_player(info["WIZTO"]) )
        {
                send_warning(info["HOSTADDRESS"],info["PORTUDP"],
                    "Affirmation warning : No such user or he is offlin now.");
                return;
        }
        if( info["MSG"][<1..<0] != '\n' ) info["MSG"] += "\n";

        tell(ob, sprintf(GRN "[ %s ] %s[%s] 告诉你 ：%s\n"NOR,undefinedp(info["TYPE"])?" ":info["TYPE"],capitalize(info["WIZFROM"]),name,info["MSG"] ), TELLMSG);

}

void send_affirmation(string targ,int port, string to,string msg, string type)
{
        mapping info;
        info = ([
            "NAME" : INTERMUD_MUD_NAME,
            "PORTUDP" : "" + udp_port,
            "WIZFROM" : type+"@"+INTERMUD_MUD_NAME,
            "WIZTO"     : to,
            "TYPE" : type,
            "MSG" : msg,
        ]);
        send_udp(targ,port,"affirmation_a",info);
        NCH_CHANNEL("send affirmation msg to "+to+"@"+targ+":"+port);
}

//--------------------------------------------------------------------------------------------
// Gtell 系列
//--------------------------------------------------------------------------------------------



void receive_gtell(mapping info)
{
        string name=get_mud_name(info);
        object ob;

        if(compare_mud_info(info)<1)
                return;
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["WIZTO"])
            ||  undefinedp(info["WIZFROM"])
            ||  undefinedp(info["MSG"])
        )   return;
        if( !test_buffer(name,GTELL_B))
        {
                if(time()-gtell_buffer[name] < 1)
                {
                        send_affirmation(info["HOSTADDRESS"],info["PORTUDP"],info["WIZFROM"],
                            "Gtell warning : Your mud send too many GTELL request in the same time , Please try again later.","gtell");
                        NCH_CHANNEL(sprintf("%s[%s:%s] gtell 太频繁 , ignore",info["NAME"],info["HOSTADDRESS"],info["PORTUDP"]));
                        return ;
                }
        }
        gtell_buffer[name]=time();

        if( !ob=find_player(info["WIZTO"]) )
        {
                send_affirmation(info["HOSTADDRESS"],info["PORTUDP"],info["WIZFROM"],
                    "GTELL warning : No such user or he is offlin now.","gtell");
                return;
        }
        if( info["MSG"][<1..<0] != '\n' ) info["MSG"] += "\n";
        if( undefinedp(info["CNAME"]) )
                tell(ob, sprintf(GRN "%s@%s(%s) 告诉你：%s"NOR,capitalize(info["WIZFROM"]),info["NAME"],name,info["MSG"] ), TELLMSG);
        else    tell(ob, sprintf(GRN "%s(%s@%s[%s]) 告诉你：%s"NOR,info["CNAME"],capitalize(info["WIZFROM"]),info["NAME"],name,info["MSG"] ), TELLMSG);

        send_affirmation(info["HOSTADDRESS"],info["PORTUDP"],info["WIZFROM"],
            "GTELL Respond : "+info["WIZTO"]+" has received your message.","gtell");

}

int send_gtell(string targ,int port,string my_id,string my_cname,string targ_id,string msg)
{
        mapping info;
        info = ([
            "NAME" : INTERMUD_MUD_NAME,
            "PORTUDP" : "" + udp_port,
            "WIZFROM" : my_id,
            "WIZTO"     : targ_id,
            "CNAME" : my_cname,
            "MSG" : msg,
        ]);
        add_affirmation_buffer(mudlist[targ+":"+port],"gtell");
        send_udp(targ,port,"gtell",info);

        NCH_CHANNEL(sprintf("%s send gtell msg to %s@%s:%s",my_id,targ_id,targ,port+""));
        return 1;
}

//--------------------------------------------------------------------------------------------
// Support 系列
//--------------------------------------------------------------------------------------------

//void send_support_answer(string targ,int port,)

void receive_support_request(mapping info)
{
        string answer;

        if(compare_mud_info(info)<1)
                return;

        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["CMD"])
            ||  undefinedp(info["ANSWERID"])
        )   return;

        if( info["CMD"]="tcp" )
                answer="no";
        else
        {
                string cmd=info["CMD"];
                if( undefinedp(service_handler[cmd]) )
                        answer="no";
                else answer = "yes";
        }

        if( answer="yes" )
        {
                send_udp(info["HOSTADDRESS"],info["PORTUDP"],"support_a",([
                        "NAME" : INTERMUD_MUD_NAME,
                        "PORTUDP" : "" + udp_port,
                        "CMD" : info["CMD"]+(!undefinedp(info["PARAM"]) ? "||PARAM:"+info["PARAM"] : ""),
                        "ANSWERID" : info["ANSWERID"],
                        "SUPPORTED" : "yes",
                    ]));
        } else
        {
                send_udp(info["HOSTADDRESS"],info["PORTUDP"],"support_a",([
                        "NAME" : INTERMUD_MUD_NAME,
                        "PORTUDP" : "" + udp_port,
                        "CMD" : info["CMD"]+(!undefinedp(info["PARAM"]) ? "||PARAM:"+info["PARAM"] : ""),
                        "ANSWERID" : info["ANSWERID"],
                        "NOTSUPPORTED" : "yes",
                    ]));
        }
}


//--------------------------------------------------------------------------------------------
// Locate 系列
//--------------------------------------------------------------------------------------------

void receive_locate_request(mapping info)
{
        string answer;

        if(compare_mud_info(info)<1)
                return;

        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["ASKWIZ"])
            ||  undefinedp(info["TARGET"])
        )   return;

        if( find_player(lower_case(info["TARGET"])) )
                answer="YES";
        else answer="NO";

        send_udp(info["HOSTADDRESS"],info["PORTUDP"],"locate_a",([
                "NAME" : INTERMUD_MUD_NAME,
                "PORTUDP" : "" + udp_port,
                "TARGET" : info["TARGET"],
                "ASKWIZ" : info["ASKWIZ"],
                "LOCATE" : answer,
            ]));
}

void send_locate_request(string my_name,string t_name)
{
        string t;
        mapping mudinfo;

        foreach(t, mudinfo in (mudlist+incoming_mudlist))
        send_udp(mudinfo["HOSTADDRESS"],mudinfo["PORTUDP"],"locate_q",([
                "NAME" : INTERMUD_MUD_NAME,
                "PORTUDP" : "" + udp_port,
                "TARGET" : t_name,
                "ASKWIZ" : my_name,
            ]));
}

void receive_locate_answer(mapping info)
{
        object ob;
        if(compare_mud_info(info)<1)
                return;

        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["LOCATE"])
            ||  undefinedp(info["ASKWIZ"])
            ||  undefinedp(info["TARGET"])
        )   return;

        switch(info["TARGET"])
        {
        case "NO":return;
        case "YES":
                if( ob = find_player(lower_case(info["ASKWIZ"])))
                        tell(ob,sprintf("%s was located on %s [%s:%s] now.\n",info["TARGET"],info["NAME"],info["HOSTADDRESS"],info["PORTUDP"]), ETCMSG);
                else return;
        }
        NCH_CHANNEL("收到 locate_answer");
}



//--------------------------------------------------------------------------------------------
// RWho 系列
//--------------------------------------------------------------------------------------------



void receive_rwho_request(mapping info)
{
        string str;
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["ASKWIZ"])
        )   return;

        if(compare_mud_info(info)<1)
                return;

        str = "/cmds/usr/who.c"->who(0, info["VERBOSE"] ? "-l": "-i");

        send_udp(info["HOSTADDRESS"],info["PORTUDP"],"rwho_a",([
                "NAME" : INTERMUD_MUD_NAME,
                "PORTUDP" : "" + udp_port,
                "ASKWIZ" : info["ASKWIZ"],
                "RWHO"  : str,
            ]));
}

void receive_rwho_answer(mapping info)
{
        object ob;
        string mudname=get_mud_name(info);

        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["ASKWIZ"])
            ||  undefinedp(info["RWHO"])
        )   return;

        if( !test_buffer(mudname,RWHO_B) )
        {
                compare_mud_info(info);
                return;
        }else sub_buffer(mudname,RWHO_B);

        if(!ob=find_player(info["ASKWIZ"]))
                return;
        tell(ob, info["RWHO"]+"\n", CMDMSG);
}

varargs void send_rwho_request(string ip,int port,string player,string arg)
{
        if(arg)
                send_udp(ip,port,"rwho_q",([
                        "NAME" : INTERMUD_MUD_NAME,
                        "PORTUDP" : "" + udp_port,
                        "ASKWIZ" : player,
                        "VERBOSE": arg,
                    ]));
        else
                send_udp(ip,port,"rwho_q",([
                        "NAME" : INTERMUD_MUD_NAME,
                        "PORTUDP" : "" + udp_port,
                        "ASKWIZ" : player,
                    ]));
        add_buffer(ip+":"+port,RWHO_B);
}

string query_name()
{
        return "INTERMUD2 系统(INTERMUD2_D)";
}

