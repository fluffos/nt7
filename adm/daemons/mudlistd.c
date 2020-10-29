// This program is a part of NT MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>
#include <socket.h>
#include <socket_err.h>
#include <time.h>
#include <localtime.h>
#include <mudlib.h>

#define IPPORT  0
#define ADDRESS 1
#define PORT    2
#define MS sprintf("%c%c", 13, 10 )
#define CC sprintf("%c", 10 )

#define DATA_PATH       "/data/daemon/mudlistd.o"
#define LIBRARY_PATH    "/home/lonely/nitan"
#define MRTGDATA        "/data/daemon/mrtg/mudlist/"
#define MSG(x)          CHANNEL_D->channel_broadcast("nch", x)
#define DEBUG(x)

mapping mudlist = allocate_mapping(0);

nosave int resolve_times = 0;
nosave string *connectsort = allocate(0);
nosave string *connect_obs = allocate(0);
nosave mapping resolvedaddress = allocate_mapping(0);
nosave mapping mud_data = allocate_mapping(0);
nosave mapping socket_obs = allocate_mapping(0);

void get_each_mud_status(int fd, string msg);
void get_each_mud_rece(int fd, mixed data);
void get_each_mud_close(int fd);
void update_mrtg_data();

int save()
{
        return save_object(DATA_PATH);
}

void connect()
{
        string address, ipport;
        string *cnt;
        int connect_times;
        int port;
        int socket_fd;
        int i;
        
        if( sizeof(connectsort) ) return;
        
        /*
         * 多线程同时获取所有的mud信息
         */
        
        cnt = keys(mudlist);
        
        for( i=0;i<sizeof(cnt);i++ )
        {
                connect_times = 0;
                
                ipport = cnt[i];
                
                map_delete(mudlist[ipport], "USERS");
                mudlist[ipport]["LAST_CONNECT_CHECK_TIME"] = time();
                mudlist[ipport]["CONNECT_FAILED_TIMES"]++;
                
                sscanf(ipport, "%s %d", address, port);
                
                if( sscanf(address, "%*d.%*d.%*d.%*d") != 4 )
                {
                        if( undefinedp(resolvedaddress[address]) )
                        {
                                continue;
                        }
                        else
                        {
                                address = resolvedaddress[address];
                        }
                }
                
                DEBUG((i+1)+". "+ipport+" 连线检查");                
                
                socket_fd = SOCKET_D->socket_open(address, port, STREAM,
                                (: get_each_mud_rece :),(: get_each_mud_close :), (: get_each_mud_status :));
                                
                if( socket_fd >= 0 )
                {
                        socket_obs += ([ socket_fd : ({ ipport, address, port }) ]);
                        SOCKET_D->socket_send(socket_fd, "gb\n");
                }
                else
                {
                        connect_times++;
                        DEBUG((i+1)+". "+ipport+" 连线逾时"+connect_times+"次");
                        socket_fd = SOCKET_D->socket_open(address, port, STREAM,
                                        (: get_each_mud_rece :),(: get_each_mud_close :), (: get_each_mud_status :));
                                        
                        if( socket_fd >= 0 )
                        {
                                socket_obs += ([ socket_fd : ({ ipport, address, port }) ]);
                                SOCKET_D->socket_send(socket_fd, "gb\n");
                        }
                        else
                        {                              
                                DEBUG((i+1)+". "+ipport+" 连线逾时失败");
                        }
                }
        }
}

void connect_check()
{
        string address, ipport;

        if( !sizeof(connectsort) )
        {
                connect();
                return;
        }

        ipport = connectsort[0];
        
        sscanf(ipport, "%s %*d", address);
        if( sscanf(address, "%*d.%*d.%*d.%*d") == 4 )
        {
                DEBUG(sizeof(connectsort)+". "+connectsort[0]+" 域名无需解析"); 
                connectsort = connectsort[1..];  
                connect_check();
                return;
        }
        else
        {
                if( !undefinedp(resolvedaddress[address]) )
                {
                        DEBUG(sizeof(connectsort)+". "+connectsort[0]+" 域名已经解析"); 
                        connectsort = connectsort[1..];                        
                        connect_check();
                        return;
                }
                
                DEBUG(sizeof(connectsort)+". "+address+" 进行名称解析");
                resolve(address, "resolve_callback");
        }                    
}

void resolve_callback(string address, string resolved, int key)
{
        string addr;
        string ipport;

        ipport = connectsort[0];

        if( !resolved )
        {
                resolve_times++;
                DEBUG(sizeof(connectsort)+". "+ipport+" 域名检查逾时"+resolve_times+"次");
                if( resolve_times > 1 )
                {
                        resolve_times = 0;
                        DEBUG(sizeof(connectsort)+". "+ipport+" 域名检查逾时失败");
                        connectsort = connectsort[1..];
                        connect_check();
                }
                else
                {
                        connect_check();
                }
        }
        else
        {
                DEBUG(sizeof(connectsort)+". "+ipport+" 域名解析成功");
                sscanf(ipport, "%s %*d", addr);
                resolvedaddress[addr] = resolved;
                
                resolve_times = 0;
                connectsort = connectsort[1..];
                connect_check();
        }
}

void get_each_mud_status(int fd, string msg)
{
        if( fd && !undefinedp(socket_obs[fd]) )
                DEBUG(sprintf("%d. 读取MUD『%s』信息状况：%s\n",
                              fd, socket_obs[fd][IPPORT], msg));
        else
                DEBUG(sprintf("%d. 读取MUD信息状况：%s\n", fd, msg));
}

void get_each_mud_rece(int fd, mixed msg)
{
        // 获取mud的login内容信息放入mud_data["fd"]中
        if( undefinedp(mud_data[fd]) )
                mud_data[fd] = msg;
        else
                mud_data[fd] += msg;
}

void get_each_mud_close(int fd)
{
        string *usercount = allocate(3);
        string ipport;
        string address;
        string msg;
        int socket_fd;
        int port;

        if( undefinedp(socket_obs[fd]) )
        {
                socket_close(fd);
                return;
        }
        
        ipport = socket_obs[fd][IPPORT];
        address = socket_obs[fd][ADDRESS];
        port = socket_obs[fd][PORT];
        
        msg = mud_data[fd];
        
        if( !sizeof(msg) )
        {
                // 读取不成功，再来一次      
                if( member_array(ipport,connect_obs) == -1 )
                {
                        socket_fd = SOCKET_D->socket_open(address, port, STREAM,
                                (: get_each_mud_rece :),(: get_each_mud_close :), (: get_each_mud_status :));
                                
                        if( socket_fd >= 0 )
                        {
                                socket_obs += ([ socket_fd : ({ ipport, address, port }) ]);
                                SOCKET_D->socket_send(socket_fd, "gb\n");
                        }
                        connect_obs += ({ ipport });
                }
        }
        else
        {
                mudlist[ipport]["LAST_CONTACT_TIME"] = time();

                map_delete(mudlist[ipport], "CONNECT_FAILED_TIMES");
                
                map_delete(mud_data, fd);
        }
        
        if( sizeof(msg)>0 && sizeof(mudlist[ipport]["USERS_COUNT_PARSE"])>0 && !mudlist[ipport]["USERS"] )
        {

                msg = remove_ansi(msg);
                if( !undefinedp(mudlist[ipport]["BIG5"]) ) msg = B2G(msg);

                sscanf( msg, "%*s"+mudlist[ipport]["USERS_COUNT_PARSE"]+"%*s", usercount[0], usercount[1], usercount[2] );

                usercount = map(usercount, (: CHINESE_D->chinese_to_number($1) :));

                mudlist[ipport]["USERS"] = implode(usercount, (:$1+$2:));
        }

        DEBUG(fd+". "+ipport+" 侦测连线状况完毕");
        socket_close(fd);
        SOCKET_D->close_socket(fd);
        map_delete(socket_obs, fd);
        
        // 所有的mud数据都读取完毕
        if( sizeof(socket_obs) < 1 )
        {
                mud_data = ([]);
                connect_obs = ({});

                save();
                MSG("MUDLIST 更新资料完毕，共 "+sizeof(mudlist)+" 组 Mud 资料");
                update_mrtg_data();
                HTML_D->create_mudlist_html();
                return;
        }
}

// 将单一 Mud 加入 MRTG
void add_mud_to_mrtg(string name)
{
        mapping info = ([
                "Directory":"mudlist/"+replace_string(name, " ", "_"),
                "Target":"`cat \""LIBRARY_PATH+MRTGDATA+name+"\"`",
                "YLegend":"user(s)",
                "LegendI":"线上人数",
                "LegendO":"",
                "Legend1":"在游戏中的线上使用者人数",
                "ShortLegend":"人",
                "Legend2":"",
                "Title": mudlist[name]["MUD_CHINESE_NAME"]+" - "+mudlist[name]["MUD_ENGLISH_NAME"]+" 人数统计列表",
                "PageTop":mudlist[name]["MUD_CHINESE_NAME"]+" - "+mudlist[name]["MUD_ENGLISH_NAME"]+" 人数统计列表"
        ]);

        // 纪录该 Mud 之线上玩家数
        write_file(MRTGDATA+name, mudlist[name]["USERS"]+"\n0", 1);

        MRTG_D->addmrtg(name, info);
}

// 将中文玩家总数加入 MRTG
void add_all_muds_to_mrtg(int alluser)
{
        string name="0_total_count";
        mapping info=allocate_mapping(0);

        info = ([
                "Directory":"mudlist/"+name,
                "Target":"`cat \""LIBRARY_PATH+MRTGDATA+name+"\"`",
                "YLegend":"user(s)",
                "LegendI":"线上人数",
                "LegendO":"MUD 间数",
                "Legend1":"在 MUDs 游戏中的线上总使用者人数",
                "Legend2":"当时所监测的 MUDs 数量",
                "ShortLegend":"&nbsp",
                "MaxBytes":10000,
                "AbsMax":20000,
                "Title": "MUDs 人数统计列表",
                "PageTop":"MUDs 人数统计列表"
        ]);

        // 纪录所有 Mud 线上玩家总数
        write_file(MRTGDATA+"0_total_count", alluser+"\n"+sizeof(mudlist), 1);

        MRTG_D->addmrtg(name, info);
}

// 更新 MRTG 资讯
void update_mrtg_data()
{
        int i;
        int hour;
        int alluser = 0;

        foreach( string name , mapping m in mudlist )
        {
                if( !stringp(name) || !mapp(m) ) continue;

                // 分散处理
                call_out((:add_mud_to_mrtg, name:), ++i*2);

                alluser += m["USERS"];
        }

        hour = TIME_D->query_realtime_array()[HOUR];
        if( alluser > DB_D->query_data("mudlist/maxusers/hour/"+hour) )
                DB_D->set_data("mudlist/maxusers/hour/"+hour, alluser);

        add_all_muds_to_mrtg(alluser);
}

varargs void reset_maxuser(int hour)
{
        if( !hour ) hour = localtime(time())[LT_HOUR];
        DB_D->delete_data("mudlist/maxusers/hour/"+hour);
}

void distributed_connect()
{
        if( sizeof(connectsort) ) return;

        connectsort = keys(mudlist);
        connect_check();

        //update_mrtg_data();
        MSG("MUDLIST 开始取得资讯");
}

void change_ipport(string old_ipport, string new_ipport)
{
        if( undefinedp(mudlist[old_ipport]) )
                return;

        connectsort = allocate(0);

        mudlist[new_ipport] = copy(mudlist[old_ipport]);
        map_delete(mudlist, old_ipport);

        distributed_connect();
        save();
}

void add_mud(string ipport)
{
        if( !mapp(mudlist[ipport]) )
                mudlist[ipport] = allocate_mapping(0);

        connectsort = allocate(0);

        distributed_connect();
        save();
}

void add_mud_info(string ipport, string key, string value)
{
        if( !mapp(mudlist[ipport]) )
                add_mud(ipport);

        mudlist[ipport][key] = value;
}

void remove_mud_info(string ipport, string key)
{
        if( !mapp(mudlist[ipport]) ) return;

        map_delete(mudlist[ipport], key);
}

void remove_mud(string ipport)
{
        MRTG_D->removemrtg(replace_string(ipport, " ", "_"));
        map_delete(mudlist, ipport);

        connectsort = allocate(0);

        distributed_connect();

        save();
}

mapping query_mudlist()
{
        return mudlist;
}

int remove()
{
        //socket_close(fd);

        return save();
}

void create()
{
return;
        if( !restore_object(DATA_PATH) )
                save();

        distributed_connect();
}
string query_name()
{
        return "泥巴列表系统(MUDLIST_D)";
}
