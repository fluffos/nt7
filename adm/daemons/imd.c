/* *********************网路即时通讯系统***********************
*  
*                                                  By Whatup *
*                                               
* 离线
:whatup_!whatup@mail2000.com.tw QUIT :Leaving...
上线
:whatup_!whatup@mail2000.com.tw JOIN :#bitlbee
    :root!root@localhost.localdomain PRIVMSG #bitlbee :Question on MSN connection (handle yukang.tw@yahoo.com.tw):
    :root!root@localhost.localdomain PRIVMSG #bitlbee :The user whatup.tw@gmail.com (□蝻-舀踵) wants to add you to his/her buddy list. Do you want to allow this?
    :root!root@localhost.localdomain PRIVMSG #bitlbee :You can use the yes/no commands to answer this question.

*                                     ==未经同意，严禁流出==  *
**************************************************************/

/* 标头引入档 */
#include <ansi.h>
/* 侦错设定 */
#include <net/socket.h>
#include <net/socket_errors.h>

#define PING_TIME 240
#define TELL(x) CHANNEL_D->do_channel(this_object(),"sys", x);
#define BITLBEE_SERVER "127.0.0.1 6667"

#define DEBUG   1

inherit F_DBASE;

/* 启始设定 */
nosave mapping users = ([]);

protected int process_identify(object me,string pass);
void process_who(int fd,string str);
protected void close_socket(int fd);
varargs void send_who(int fd,string id);
void send_ping();

/* 档案主档 */
void create()
{
        set("channel_id", "通讯精灵");
        seteuid(getuid());

#ifdef DEBUG
        TELL(sprintf("[%s]启始完成。", TIME_D->replace_ctime(time()) ));
#endif 

        call_out((:send_ping:),PING_TIME);
}

void send_ping()
{
        foreach(int fd,mapping m in users)
        {
                socket_write(fd,"PING\r\n");
        }
        call_out((:send_ping:),PING_TIME);
}

void remove()
{
        foreach(int fd,mapping m in users)
        {
                if(m["obj"])
                        tell_object(m["obj"],"重新更新 im 系统，请重新登入。\n");
                socket_write(fd,"QUIT\r\n");
                socket_close(fd);
        }
}

void reset()
{
        foreach(int fd,mapping m in users)
        {
                if(!m["obj"]) {
                        close_socket(fd);                       
                        map_delete(users,fd);
                }
        }
}

/* 开始登入 */
void login_irc(object user)
{
        int err,fd;
        string id;
        id=query("id", user);
        if(!id)
        {
                tell_object(user,"你没有登入 ID ");
                return ;
        }
        fd = socket_create(STREAM, "read_callback","close_socket");
        if ( fd < 0 )
        {
                tell_object(user,"连结失败，可能是主机没有开启或是网路无法连线。");
                return;
        }
        users[fd] = allocate_mapping(5);
        users[fd]["id"] = id;
        users[fd]["steps"]   = 0;
        users[fd]["obj"]   = user;
        users[fd]["list"] = allocate_mapping(1);
        set_temp("im_fd", fd, user);

        err = socket_connect(fd,BITLBEE_SERVER,"read_callback","write_callback" );
        if( err==EESUCCESS )
        {
#ifdef DEBUG
                TELL(sprintf("[%s] %s 成功\启动 Socket ,开始准备登入 irc.fd = %d",
                        TIME_D->replace_ctime(time()) ,id,fd));
#endif 
        }
        else
        {
#ifdef DEBUG
                TELL(sprintf("[%s]启动 Socket 失败,无法送连结网路主机.",
                        TIME_D->replace_ctime(time()) ));
#endif 
                return ;
        }
        call_out((:process_identify:),3,user,crypt(id,id)[0..10]);
        return;
}

protected int process_identify(object me,string pass)
{
        int fd=query_temp("im_fd", me);
        if( fd < -1 ) 
        {
                tell_object(me,"[IM Message]:连线失败，请稍后再试！\n");
                return 1;
        }
        if(users[fd]["obj"] == me)
                socket_write(fd,"PRIVMSG #bitlbee :identify "+pass+"\r\n");
}

protected void write_callback(int fd)
{
TELL(sprintf("%d",fd));
        socket_write(fd,"NICK "+users[fd]["id"]+"\r\n");
        return ;
}

protected void read_callback(int fd,mixed message)
{
        string str;
#ifdef DEBUG
        TELL(sprintf("[%s] %d,%s",
                TIME_D->replace_ctime(time()),fd,message ));
#endif DEBUG
        if(regexp(message ,"PING :PinglBee") ) //PING :PinglBee
        {
                socket_write(fd,"PONG\r\n");
        } 

        if( !mapp(users[fd]) ) return;

        switch(users[fd]["steps"])
        {
        case 0:
                str = sprintf("USER %s %s %s :%s\r\n",users[fd]["id"],
                    users[fd]["id"],query_ip_name(users[fd]["obj"]),
                    query("name", users[fd]["obj"]));
                socket_write(fd,str);
                break;
        case 1:
                str = sprintf("JOIN #bitlbee\r\n");
                socket_write(fd,str);
                break;
        case 2:
                str = sprintf("MODE #bitlbee\r\n");
                socket_write(fd,str);
                break;
        case 3:
                str = sprintf("WHO #bitlbee\r\n");
                socket_write(fd,str);
                str = sprintf("PRIVMSG #bitlbee :set charset=gb2312\r\n");
                socket_write(fd,str);
                break;
        default:

                {
                        string name,mail,msg,id;
                        //:whatup_!whatup@mail2000.com.tw PRIVMSG #bitlbee :whatup: test
                        foreach(string m in explode(message,"\r\n")) 
                        { 
                                if(sscanf(m,":%s!%s PRIVMSG #bitlbee :%s",name,mail,msg) == 3 )
                                {
                                        //:root!root@localhost.localdomain PRIVMSG #bitlbee :The user whatup.tw@gmail.com (□蝻-舀踵) wants to add you to his/her buddy list. Do you want to allow this?
                                        if(sscanf(msg,"The user %s wants to add you to his/her buddy list. Do you want to allow this?",mail) == 1)
                                        {
                                                tell_object(users[fd]["obj"],"\n[IM Message]:"+mail+"想要把你加入他的好友名单，同意的话用 im yes，不同意的话，用 im no。\n");
                                        }
                                        else if(sscanf(msg,"%s: %s",id,msg) == 2  && users[fd]["obj"]
                                            && id == users[fd]["id"])
                                                tell_object(users[fd]["obj"],sprintf(HIW HBBLU"%s 用即时讯息传给你 : %s\n"NOR,
                                                        users[fd]["list"][name][4]+"("+users[fd]["list"][name][0]
                                                        +"@"+users[fd]["list"][name][1]+")\n["+name+"]",msg));
                                        else 
                                                switch(msg)
                                        {
                                        case "The nick is (probably) not registered":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:第一次使用该精灵，自动注册帐号！\n");
                                                socket_write(fd,"PRIVMSG #bitlbee :register "+crypt(users[fd]["id"],users[fd]["id"])[0..10]+"\r\n");
                                                break;
                                        case "Incorrect password":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:登入密码错误(请通知系统管理员)！\n");
                                                break;
                                        case "YAHOO - Login error: Error 99 (Logged in on a different machine or device)":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:你已在其他电脑登入 YAHOO！\n");
                                                break;
                                        case "MSN - Logged out: Someone else logged in with your account":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:你已在其他电脑登入 MSN ！\n");
                                                break;
                                        case "YAHOO - Signing off..":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:你登出 YAHOO ！\n");
                                                break;
                                        case "MSN - Signing off..":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:你登出 MSN ！\n");
                                                break;
                                                //                            case "MSN - Logging in: Authenticated, getting buddy list":
                                        case "MSN - Logged in":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:MSN 登入成功！\n");
                                                break;
                                        case "YAHOO - Logged in":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:YAHOO 登入成功！\n");
                                                break;
                                        case "No accounts known. Use 'account add' to add one.":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:请使用 im register msn 或是 im register yahoo 注册帐号！\n");
                                                break;
                                        case "MSN - Login error: Error during Passport authentication":
                                                tell_object(users[fd]["obj"],"\n[IM Message]:MSN密码错误！\n");
                                                break;
                                        default:
                                        }
                                }

                                // 上站讯息 :paiting!paiting@hotmail.com JOIN :#bitlbee
                                if(sscanf(m,":%s!%s JOIN :#bitlbee",id,name) == 2)
                                {
                                        send_who(fd,id);
                                        tell_object(users[fd]["obj"],"\n[IM Message]:"+id+"上线了 ！\n");
                                        continue;
                                }
                                // 下站讯息 :paiting!paiting@hotmail.com QUIT :Leaving...
                                if(sscanf(m,":%s!%s QUIT :Leaving...",id,name) == 2)
                                {
                                        map_delete(users[fd]["list"],id);
                                        tell_object(users[fd]["obj"],"\n[IM Message]:"+id+"离线了 ！\n");
                                        continue;
                                }
                                // 状况变线上 :root!root@rw.twku.net MODE #bitlbee +v paiting
                                if(sscanf(m,":root!root@rw.twku.net MODE #bitlbee +v %s",id) == 1)
                                {
                                        send_who(fd,id);
                                        continue;
                                }
                                // 状况变away或忙录 :root!root@rw.twku.net MODE #bitlbee -v paiting
                                if(sscanf(m,":root!root@rw.twku.net MODE #bitlbee -v %s",id) == 1)
                                {
                                        send_who(fd,id);
                                        continue;
                                }
                                if(sscanf(m,":%*s 352 %*s %*s %*s %*s %*s %*s %*s :%*d %*s") == 10) 
                                {
                                        process_who(fd,m);
                                } else 
                                if(sscanf(m,":%*s 352 %*s #bitlbee %*s %*s %*s %*s %*s :%*d %*s") == 9) 
                                {
                                        process_who(fd,m);
                                }


                        }
                }
        }
        users[fd]["steps"]++;   
}

#ifdef DEBUG
void socket_write(int fd,mixed message)
{
        int i;
        TELL(sprintf(HIR"[%s] %d,%s"NOR,
                TIME_D->replace_ctime(time()),fd,message ));
        i = efun::socket_write(fd,message);
        switch(i)
        {
        case EEFDRANGE:       TELL("描述值 (descriptor) 超出范围。"); break;
        case EEBADF:          TELL("无效的描述值。"); break;
        case EESECURITY:      TELL("企图违反安全。"); break;
        case EENOADDR:        TELL("socket 未指定位址。"); break;
        case EEBADADDR:       TELL("位址格式的问题。"); break;
        case EENOTCONN:       TELL("socket 尚未连接。"); break;
        case EEALREADY:       TELL("操作已在进行中。"); break;
        case EETYPENOTSUPP:   TELL("不支援此物件型态。"); break;
                //        case EEBADDATA:       TELL("送出的资料含有太多巢状层次 (nested level)。"); break;
        case EESENDTO:        TELL("sendto 的问题。"); break;
        case EEMODENOTSUPP:   TELL("不支援此 socket 型态。"); break;
        case EEWOULDBLOCK:    TELL("操作将会停滞 (block)。"); break;
        case EESEND:          TELL("送出 (send) 的问题。"); break;
        case EECALLBACK:      TELL("等待回呼 (callback) 中。"); break;
        default:

        }
}
#endif

protected void close_socket(int fd)
{
        if(users[fd]["obj"])
                delete_temp("im_fd", users[fd]["obj"]);

        map_delete(users,fd);
        socket_close(fd);
#ifdef DEBUG
        TELL(sprintf("[%s] %d,连线结束",
                TIME_D->replace_ctime(time()),fd ));
#endif
}

void send_command(int fd,mixed message)
{
        socket_write(fd,message+"\r\n");
#ifdef DEBUG    
        TELL(sprintf("[%s] %d,%s",
                TIME_D->replace_ctime(time()),fd,message ));
#endif
}
// 处理 irc 线上使用者
varargs void send_who(int fd,string id)
{
        if(undefinedp(id))   socket_write(fd,"WHO #bitlbee\r\n");
        else    socket_write(fd,"WHO "+id+"\r\n");

}
void process_who(int fd,string str)
{
        string id,ip,status,nick,name;
        //:rw.twku.net 352 whatup #bitlbee whatup 218-184-22-55.cm.dynamic.apol.com.tw rw.twku.net whatup H :0 小ｘ儿
        if(sscanf(str,":%*s 352 %*s #bitlbee %s %s %*s %s %s :%*d %s",
                id,ip,name,status,nick) == 9) 
                users[fd]["list"][name] = ({ id,ip,name,status,nick});
        //:rw.twku.net 352 whatup whatup_ whatup mail2000.com.tw rw.twku.net whatup_ H :0 鱼缸-有谁要 gmail 帐号，我有一堆-.
        //:%*s 352 %*s %*s %s %s %*s %s %s :%*d %*s
        if(sscanf(str,":%*s 352 %*s %*s %s %s %*s %s %s :%*d %s",
                id,ip,name,status,nick) == 10) 
                users[fd]["list"][name] = ({ id,ip,name,status,nick});
}

int process_send_msg(object me,string who,string msg)
{
        int fd=query_temp("im_fd", me);
        if(undefinedp(users[fd]) &&
            !undefinedp(users[fd]["list"][who]))
                return notify_fail("[IM Message] 即时讯息上的好友名单没有这个人！\n");
        socket_write(fd,"PRIVMSG #bitlbee :"+ who + ":"+msg+"\r\n");
        {
                string *n = users[fd]["list"][who];

                // Unknown Bug ; Temporarily modified by clode
                if( !n || sizeof(n) != 5 ) return 1;
                tell_object(me,sprintf(HIW HBBLU"你用即时讯息传给 %s : %s\n"NOR,
                        n[4]+"("+n[0]+"@"+n[1]+")\n["+who+"]",msg));
        }
        return 1;
}

int del_account(int fd,string protocol) 
{
        // 要先离线，才能删掉
        socket_write(fd,"PRIVMSG #bitlbee :account off "+protocol+"\r\n");
        socket_write(fd,"PRIVMSG #bitlbee :account del "+protocol+"\r\n");
}

int register_account(int fd,string protocol,string account,string passwd)
{
        socket_write(fd,"PRIVMSG #bitlbee :account add "+protocol+" "+account+" "+passwd+"\r\n");
        socket_write(fd,"PRIVMSG #bitlbee :account on "+protocol+"\r\n");
}

mapping query_users(){ return users; }

string query_name()
{
        return "网路即时通讯系统(IM_D)";
}
