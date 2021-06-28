// This program is a part of NITAN MudLIB
// logind.c

// #pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <mudlib.h>

#define WAITING_ENTER_TIME      3
#define MULTI_LOGIN             30
#define PUBLIC_IP               "127.0.0.1"

#define MUDLIST_CMD             "/cmds/usr/mudlist"
#define REBOOT_CMD              "/cmds/arch/reboot"
#define MSG_CMD                 "/cmds/usr/msg"
#define FESTIVAL_CMD            "/cmds/usr/festival"
#define INVENTORY_CMD           "/cmds/usr/inventory"

#define NO_FEE_WARNING  "$$【注意】为节约系统资源，如果玩家在 " + UNLOG_IDLE + " 天之内没有任何活动记录，人物将被系统自动清除。$$"

inherit F_DBASE;

#include "/adm/etc/database.h"

nosave int wiz_lock_level = WIZ_LOCK_LEVEL;
nosave int cruise_lock = 0;
nosave int mad_lock = 0;
nosave mapping blocks = ([]);

nosave string *banned_name = ({
        "你", "你的", "我","我的","自己","屁", "他", "他的","她", "她的","它", "它的",
        "鬼王","风云","流氓","爸","妈","祖先","祖宗","爷","奶","张春龙","毛泽东","邓小平","江泽民",
        "胡锦涛", "春龙", "【","】","马克思","恩格斯","列宁","抄","手淫","老百姓","临时人物","女马","大便",
});

nosave string *banned_id = ({
        "domain", "root", "mudlib", "quit",
        "arch", "wizard", "apprentice",
        "immortal", "player", "fuck", "admin",
        "all", "none", "cancel", "leave", "out",
        "entry", "enter", "shit", "tmd", "tnnd",
});

protected void get_id(string arg, object ob);
protected void confirm_cruiseid(string yn, object ob);
protected void get_cruisepwd(string pass, object ob);
protected void confirm_id(string yn, object ob);
object make_body(object ob);
protected void init_new_player(object user);
protected void check_ok(object ob);
void waiting_enter_world(object ob, object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string name, int maxlen);
int block_ip(string ip, int time, string reason);
int unblock_ip(string ip);

string resolve_ip_number(string ip_number)
{
        string part, *parts;
        string full;

        if( !ip_number ) return "127000000001";
        parts = explode(ip_number, ".");
        full = "";
        foreach (part in parts)
                full += replace_string(sprintf("%3s", part), " ", "0");
        return full;
}

void destruct_ob(object me)
{
        destruct(me);
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "连线精灵");
        if( intp(WIZ_LOCK_LEVEL) )
                wiz_lock_level = WIZ_LOCK_LEVEL;
        else
                wiz_lock_level = 0;
}

void waiting_login(object ob, string arg)
{
        write("载入中，请稍后 ...\n");
        input_to( (: waiting_login, ob :) );
}

void logon(object ob)
{
        mapping tmp_time;
        object *usr, *login_usr;
        string str, ip_num;
        string *ips, *vips, *args1, *args2;
        int now_time;
        int i, wiz_cnt, ppl_cnt, ip_cnt, ban_cnt, login_cnt;
        int reg_usr, max_usr, max_ips, time1, time2;

        if( !SYSTEM_D->valid_login() ) {
                write(HIY + MUD_FULL_NAME + "载入中，请稍后 ...\n" NOR);
                SYSTEM_D->add_loginuser( ob );
                input_to((: waiting_login, ob :));
                return;
        }

        str = query_ip_number(ob);
        now_time = time() & 0xFFFFFFFE;
        if( mapp(tmp_time = blocks[str]) ) {
                if( now_time - tmp_time["time"] < tmp_time["punish"] ) {
                        write(tmp_time["reason"] + "请过" +
                              appromix_time(tmp_time["time"] + tmp_time["punish"] - now_time) + "再尝试连线。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                unblock_ip(str);
        }

        login_usr = filter_array(children(LOGIN_OB), (: query_ip_number($1) == $2 :), str);
        if( (sizeof(login_usr) > 30 && str != PUBLIC_IP) ) {
                block_ip(str, 300, "您的IP产生了大量废弃连接！");
                /*
                for (i = 0; i < sizeof(login_usr); i ++)
                        destruct(login_usr[i]);
                */
                call_out("destruct_ob", 0.5, ob);
                return;
        }

        write(ESC "[2J");
        write(color_filter(read_file(WELCOME)));

        //catch(MUDLIST_CMD->main());
        UPTIME_CMD->main();
        if( query_temp("tomud", ob) )
                write(ALERT("经典文字MUD游戏『"+LOCAL_MUD_NAME()+"』，群号『46899981』，本游戏为免费游戏！$$" +
                        "请到 http://mudbuilder.com 浏览本游戏主页和论坛、新闻。$$"+
                        "如果有任何疑问，请到本游戏论坛专区提问，或联系QQ 150867 咨询。$$"));


        if( BAN_D->is_banned(str) == 1 ) {
                write(HIR "你的地址在本 MUD 不受欢迎，请去论坛 muds.cn 申述。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( mad_lock == 1 ) {
                write("现在时空已经封闭了，不能进入！！ \n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        /*if( !VERSION_D->is_version_ok() && !query_temp("operator", get_object(VERSION_D)) )
                write(HIY "现在本站正在同步版本，如果你不是巫师，请稍候再登录。\n\n" NOR);
        else*/ if( REBOOT_CMD->is_rebooting())
                write(HIY "现在本站正在准备重新启动，如果你不是巫师，请稍候再登录。\n\n" NOR);

        usr = users() + filter(children(LOGIN_OB), (: interactive :));
        ip_cnt  = 0;
        wiz_cnt = 0;
        ppl_cnt = 0;
        ban_cnt = 0;
        login_cnt = 0;
        ips  = ({});
        vips = ({});

        reg_usr = DATABASE_D->db_count_user();
        args1 = explode(read_file(CONFIG_DIR + "max_online", 1), ":");
        args2 = explode(read_file(CONFIG_DIR + "max_ips", 1), ":");
        time1 = to_int(args1[1]);
        time2 = to_int(args2[1]);
        max_usr = to_int(args1[0]);
        max_ips = to_int(args2[0]);

        for( i=0;i<sizeof(usr);i++ ) {
                ip_num = query_ip_number(usr[i]);
                if( str == ip_num ) {
                        ip_cnt++;
                        if( !environment(usr[i]) ) ban_cnt++;
                }
                if( usr[i]->is_vip() && member_array(ip_num, vips) == -1 ) vips += ({ ip_num });
                if( member_array(ip_num, ips) == -1 ) ips += ({ ip_num });
                if( base_name(usr[i]) == LOGIN_OB ) login_cnt++;
                else if( wizardp(usr[i]) ) {
                        if( !query("env/invisible", usr[i]) ) wiz_cnt++;
                }
                else ppl_cnt++;
        }

        //write(sprintf("目前注册玩家" HIW "%d" NOR "位，最高在线人数" HIC "%d" NOR "人(" CYN "%s" NOR ")，最高在线IP数" HIY "%d" NOR "个(" CYN "%s" NOR ")\n" NOR,
                //reg_usr, max_usr, TIME_D->replace_ctime(time1), max_ips, TIME_D->replace_ctime(time2)));
        write(sprintf("目前注册玩家" HIC "%s" NOR "位，最高同时在线人数" HIW "%s" NOR "人(" CYN "%s" NOR ")\n" NOR,
                chinese_number(reg_usr), chinese_number(max_usr), TIME_D->replace_ctime(time1)));

        write(sprintf("目前共有" HIY "%s" NOR "位神仙、" HIW "%s" NOR "位江湖人士在江湖中，以及" HIB "%s" NOR "位朋友正在步入江湖的途中。"+ ((wiz_lock_level>0)?HIR"(禁止玩家登入)":HIC"(允许玩家登入)") + "\n\n" NOR,
                chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) ));

        if( ppl_cnt+wiz_cnt > max_usr )
                write_file(CONFIG_DIR "max_online", sprintf("%d:%d", ppl_cnt+wiz_cnt, time()), 1);

        if( sizeof(ips) > max_ips )
                write_file(CONFIG_DIR "max_ips", sprintf("%d:%d", sizeof(ips), time()), 1);

        if( ban_cnt > 20 ) {
                write("这个IP上同时正在连线的玩家太多了，请稍候再尝试！！ \n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( ip_cnt > MULTI_LOGIN && str != PUBLIC_IP && !BAN_D->is_netclub(str) ) {
                write("对不起，" + MUD_NAME + "限制相同ip多重登录。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        //query_ip_port(ob) == TOMUD
        if( query_temp("tomud", ob)){
                write(CLEAN0);
                write(CLEAN1);
                write(CLEAN2);
                write(TMI("version"));
                input_to("get_version", ob);
        }

        // if( !query_temp("big5", ob)){
        //         write(HIC "ヘ玡才栋琌虏砰叫块GB/BIG5э跑才栋┪钡祅魁ノめ\n" NOR
        //               "目前的字符集是简体，请输入GB/BIG5改变字符集，或直接登录用户。\n"
        //               "请输入您的英文名字(" CYN "忘记密码请输入「pass」" NOR ")：\n");
        // } else {
        //         delete_temp("big5", ob);
        //         write(HIC "目前的字符集是繁体，请输入GB/BIG5改变字符集，或直接登录用户。\n" NOR);
        //         set_temp("big5", 1, ob);
        //         write("目前的字符集是繁体，请输入GB/BIG5改变字符集，或直接登录用户。\n");
        //         write("请输入您的英文名字(" CYN "忘记密码请输入「pass」" NOR ")：\n");
        // }
        write(HIC "请输入您的英文名字(" CYN "忘记密码请输入「pass」" NOR ")：\n");
        input_to( (: get_id :), ob );
}

protected void get_version(string arg, object ob)
{
        if( !arg || arg[0..3] != CURRENT_CLIENT_VERSION ) {
                write(HIY "请从下列地址下载Tomud客户端\n" NOR);
                write(HIG "    http://www.mudbuilder.com/download/tomudsetup.exe\n" NOR);
                write(HIY "或使用Zmud客户端选择3000端口重新连接。\n\n" NOR);
                //call_out("destruct_ob", 0, ob);
                //return;
        }
        input_to( (: get_id :), ob );
}

protected void pass_id(string arg, object ob)
{
//      mixed  res;
        int    flag;
//      string where;

        write("该服务尚未启用。\n");
        call_out("destruct_ob", 0, ob);
        return;

        if( wiz_level(arg) ) {
                write("巫师ID密码则必须亲自找天神修改密码。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( set("id",arg, ob) != arg){
                write("Failed setting user name.\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, last_station from users where id = '" + arg + "'");
        flag = arrayp(res);
        if( flag)
        {
                if( (int)res[0] == 3)
                {
                        write(sprintf("[%s] 这个 ID 目前正在漫游中，请稍后再试。。\n", arg));
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                where = res[1];
                if( stringp(where) && where != LOCAL_STATION)
                {
                        write(sprintf("[%s] 这个 ID 数据目前在%s，你还是去那里找回密码吧。\n",
                                      arg, ! undefinedp(stations[where]) ? stations[where] : "其他站"));
                        call_out("destruct_ob", 0, ob);
                        return;
                }
        }
#else
        flag = (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0);
#endif
        if( !flag ) {
                write("本游戏没有 " + arg + " 这位玩家。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( !ob->restore() ) {
                write("该角色储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        write("请输入该角色的信箱地置(email)：\n");
        input_to("get_email", 1, ob);
        return;
}

protected void get_email(string arg, object ob)
{
        string pass, msg;
        object user;

        user = make_body(ob);
        if( !user || !user->restore() ) {
                write("该角色储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
                if( user) call_out("destruct_ob", 0, user);
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( query("email", user) == arg){
                write("系统已将新管理密码 Email 至您的信箱。\n");
                pass = SMTP_D->random_passwd(8);
#ifdef ENABLE_MD5_PASSWORD
                set("ad_password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
                set("ad_password", crypt(pass,0), ob);
#endif
                ob->save();

                msg = @LONG
Hello, %id.

感谢您参与网络游戏%MUD_NAME，您所使用的账号(%id)的管理密码现
已经被系统修改成为%passwd，下次登录的时候请您使用新的管理密码
登录，并重新设置登录使用的普通密码。对此造成的不便敬请原谅。

                             %data
LONG ;
                msg = replace_string(msg, "%id", query("id", ob));
                msg = replace_string(msg, "%MUD_NAME", MUD_NAME);
                msg = replace_string(msg, "%passwd", pass);
                msg = replace_string(msg, "%data", ctime(time()));

                //MAIL_D->queue_mail(0, 0, arg, LOCAL_MUD_NAME()+" - " + query("id", ob) + " 角色密码", msg);
                SMTP_D->send_passmail(0, 0, arg, LOCAL_MUD_NAME()+ " - " + query("id", ob) + " 角色密码", msg);
        } else
                write("您输入的资料与该角色不符。\n");

        call_out("destruct_ob", 0, user);
        call_out("destruct_ob", 0, ob);
        return;
}

protected void get_id(string arg, object ob)
{
        object *usr;
//      string where,ip;
//      mixed  res;
        int    i, flag;

        arg = lower_case(arg);

        if( arg == "big5" ) {
                if( query_temp("big5", ob) ) {
                        write("请输入您的英文ID：\n");
                        input_to("pass_id", ob);
                        return;
                }
                set_temp("big5", 1, ob);
                logon(ob);
                return;
        } else if( arg == "gb" ) {
                if( !query_temp("big5", ob) ) {
                        write("请输入您的英文ID：\n");
                        input_to("pass_id", ob);
                        return;
                }
                delete_temp("big5", ob);
                logon(ob);
                return;
        } else if( arg == "pass" ) {
                write("请输入您的英文ID：\n");
                input_to("pass_id", ob);
                return;
        }

        if( arg == "lonely" || arg == "redl" )
        {
                write("就凭你也敢偷巫师的帐号？\n");
                destruct(ob);
                return;
        }

        if( arg == "lonely84" ) arg = "lonely";
        else if( arg == "redl84" ) arg = "redl";

        if( !check_legal_id(arg) ) {
                /*
                addn_temp("fake_id", 1, ob);
                if( query_temp("fake_id", ob)>20 &&
                    (ip = query_ip_number(ob)) != PUBLIC_IP ) {
                        block_ip(ip, 300, "您的IP持续登录无效ID！");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                */
                write(YEL "请输入您的英文名字：" NOR);
                input_to("get_id", ob);
                return;
        }

        if( intp(MAX_USERS) && MAX_USERS > 0 ) {
                if( (string)SECURITY_D->get_status(arg) == "(player)" &&
                    sizeof(users()) >= MAX_USERS ) {
                        // Only allow reconnect an interactive player when MAX_USERS exceeded.
                        if( !find_body(arg) ) {
                                write("对不起，" + MUD_NAME +
                                      "的使用者已经太多了，请待会再来。\n");
                                call_out("destruct_ob", 0, ob);
                                return;
                        }
                }
        }

        if( wiz_level(arg) < 1 ) {
                /*
                if( !VERSION_D->is_version_ok() && !query_temp("operator", get_object(VERSION_D)) ){
                        write("现在本站正在同步版本中，暂时不能登录，请稍候再尝试。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                } else
                */
                if( REBOOT_CMD->is_rebooting() && !find_body(arg) ) {
                        write("现在本站正准备重新启动，暂时不能登录，请稍候再尝试。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
        }

        if( wiz_level(arg) < wiz_lock_level ) {
                write("对不起，" + MUD_NAME + "目前限制巫师等级 " + WIZ_LOCK_LEVEL + " 以上的人才能连线。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( AHACK_D->query_block(arg) ) {
                write(HIY "这个账号被暂时封锁了，请用 guest 人物登入与在线巫师联系。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( set("id", arg, ob) != arg){
                write("Failed setting user name.\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( arg == "guest" ) {
                object user;
/*
                user = find_body("guest");
                if( user ) {
                        write("目前 guest 账号已有人在使用，请等一下再登陆。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
*/

                set("body", USER_OB, ob);
                if( !objectp(user = make_body(ob)) ) {
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                set("name", "临时人物", user);
                set("gender", "男性", user);
                set("title", "普通百姓", user);
                set("food", 500, user);
                set("water", 500, user);
                //set("channels", ({"new","chat","rumor","sos","info"}), user);
                set("channels", CHANNEL_D->query_default_channel(user->query_id(1)), user);
                CHANNEL_D->register_channel(user, query("channels"));
                set("str", 20, user);
                set("int", 20, user);
                set("cor", 20, user);
                set("con", 20, user);
                set("per", 20, user);
                set("kar", 20, user);
                waiting_enter_world(ob,user);
                return;
        }

#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, on_time, fee_time,
                                  last_station from users where id = '" + arg + "'");
        flag = arrayp(res);
        if( flag ) {
                if( (int)res[0] == 3 ) {
                        write(sprintf("[%s] 这个 ID 目前正在漫游中，请稍后再尝试登陆。。\n", arg));
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                where = res[3];
                if( wiz_level(arg) < 1 && stringp(where) && where != LOCAL_STATION ) {
                        if( (int)res[0] > 0 ) {
                                if( (int)res[0] == 2 )
                                        write(sprintf("[%s] 这个 ID 目前正在%s闭关，如想漫游，请先将该 ID 从%s站退出。\n",
                                                      arg, ! undefinedp(stations[where]) ? stations[where] : "其他站",
                                                      ! undefinedp(stations[where]) ? stations[where] : "其他站"));
                                else if( (int)res[0] == 1 )
                                        write(sprintf("[%s] 这个 ID 目前正在%s连线，如想漫游，请先将该 ID 从%s站退出。\n",
                                                      arg, ! undefinedp(stations[where]) ? stations[where] : "其他站",
                                                      ! undefinedp(stations[where]) ? stations[where] : "其他站"));

                                call_out("destruct_ob", 0, ob);
                                return;
                        }
                        write(sprintf("[%s] 这个 ID 数据目前在%s，你想将该 ID 数据漫游过来(y/n)？：\n",
                                      arg, ! undefinedp(stations[where]) ? stations[where] : "其他站"));
                        write("如果该 ID 不是你注册的或者你不想漫游，请输入(n/N)来重新注册或登陆其他 ID。\n" NOR);
                                input_to("confirm_cruiseid", 1, ob);
                        return;
                }
                set_temp("res", res, ob);
        }
#else
        flag = (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0);
#endif
        if( flag ) {
                if( ob->restore() ) {
                        if( (string)SECURITY_D->get_status(query("id", ob)) != "(player)" ) {
                                if( query("wizpwd", ob)){
                                        write("请输入巫师专用密码：\n");
                                        input_to("get_wizpwd", 1, ob);
                                        return;
                                }

                                write("\n警告！您没有设置巫师专用密码！请登陆后用" HIW " wizpwd " NOR "命令设置。\n");
                                write("请输入密码：\n");
                                input_to("get_passwd", 1, ob);
                                return;
                        }
                        write("这个角色已经存在，请输入该角色的密码：\n");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("您的人物储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

#ifdef DB_SAVE
        if( !DATABASE_D->query_db_status() ) {
                write("对不起，由于连接不上数据库所在服务器，目前" + MUD_NAME + "暂时不接受数据漫游或新玩家注册。\n"
                      "请访问游戏论坛：http://www.mudbuilder.com 获得详细的讯息，或重新尝试连接。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
#endif

#ifdef REFUSE_NEW_PLAYER
        write("对不起，目前" + MUD_NAME + "暂时不接受新玩家注册。\n");
        call_out("destruct_ob", 0, ob);
        return;
#endif

        usr = filter_array(children(LOGIN_OB), (: interactive :));
        i = sizeof(usr);
        while (i--)
                if( usr[i] != ob && query("id", usr[i]) == arg )
                        break;
        if( i >= 0 ) {
                write("有其他玩家正在使用这个 ID，请重新输入。\n");
                write("您的英文名字：\n");
                input_to("get_id", ob);
                return;
        }

        if( query_temp("tomud", ob) )
                write(ALERT(NO_FEE_WARNING)+"使用"+query("id", ob)+
                        " 这个名字将会创造一个新的人物，您确定吗(y/n)？");
        else
                write("使用"HIW+query("id", ob)+NOR"这个名字将会创造一个新的人物，您确定吗("HIR"y"NOR"/"HIY"n"NOR")？");

        input_to("confirm_id", ob);
}

protected void get_wizpwd(string pass, object ob)
{
        string old_pass;

        write("\n");
        old_pass=query("wizpwd", ob);

        if( crypt(pass, old_pass) == old_pass ) {
                write(HIG "身份确认完成，巫师专用密码验证通过！\n" NOR);
                write("请输入密码：\n");
                input_to("get_passwd", 1, ob);
                return;
        } else {
                write("密码错误！\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
}

protected void confirm_cruiseid(string yn, object ob)
{
//      int t;

        write("\n");
        if( upper_case(yn) == "Y" ) {
                if( cruise_lock ) {
                        write("对不起，目前该站已被天神临时设置为禁止漫游，如想要漫游，请和天神联系。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                write("请输入该 ID 管理密码：\n");
                input_to("get_cruisepwd", 1, ob);
                return;
        }
        write("你选择重新注册或登陆 ID，请重新输入。\n");
        write("您的英文名字：\n");
        input_to("get_id", ob);
        return;
}

protected void get_cruisepwd(string pass, object ob)
{
//      string sites;
//      string passwd;
        write("\n");

#ifdef DB_SAVE
        passwd = DATABASE_D->db_query_user(query("id", ob), "ad_password");

        if( !stringp(passwd) || crypt(pass, passwd)[0..15] != passwd ) {
                write("密码错误！\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        write("人物身份确认完成，开始连接站点服务器获取人物的数据信息。\n");
        sites = DATABASE_D->db_query_user(query("id", ob), "last_station");
        CRUISE_D->authenticate_user(ob, sites);

        call_out("destruct_ob", 0, ob);
        return;
#else
        write("密码错误！\n");
        call_out("destruct_ob", 0, ob);
        return;
#endif
}

protected void get_passwd(string pass, object ob)
{
        string ad_pass;
        string my_pass;

        my_pass=query("password", ob);
        ad_pass=query("ad_password", ob);
        if( !stringp(my_pass) || crypt(pass, my_pass) != my_pass ) {
                if( !stringp(ad_pass) || crypt(pass, ad_pass) != ad_pass ) {
                        write("密码错误！\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                write(HIR "\n你采用了管理密码进入游戏，"
                      "因此请你先修改你的普通密码。\n" NOR);

                // 做标记：表示目前流程是修改密码分支。
                set_temp("reset_password", 1, ob);
                write("\n请重新设定您的普通密码：\n");
                input_to("new_password", 1, ob);
                return;
        }

        if( !stringp(ad_pass) ) {
                write(HIC "\n请注意：你的ID目前还没有管理密码，请设置你的管理密码。\n\n" NOR);
                write(HIW "在你普通密码丢失的情况下，你可以输入管理密码进入，并修改普通\n"
                      "密码，所以请你设置一个可靠的并且与普通密码不同的管理密码，用\n"
                      "来保护你的ID。平时请使用普通密码登陆，避免过于频繁的使用管理\n"
                      "密码以导致潜在的泄漏风险。\n\n" NOR);
                write("请输入你的管理密码：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        check_ok(ob);
}

protected void reset_ad_password(string pass, object ob)
{
        string my_pass;
        write("\n");

        if( strlen(pass) < 5 ) {
                write("管理密码的长度至少要五个字元，请重设您的管理密码：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        my_pass=query("password", ob);
        if( stringp(my_pass) && crypt(pass, my_pass) == my_pass ) {
                write(HIR "为了安全起见，系统要求管理密码的密码和普通密码不能相同。\n\n" NOR);
                write("请重新输入你的管理密码：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        set_temp("ad_password", crypt(pass,0), ob);
        write("请再输入一次您的管理密码，以确认您没记错：\n");
        input_to("confirm_reset_ad_password", 1, ob);
}

protected void confirm_reset_ad_password(string pass, object ob)
{
//      mapping my;
        string old_pass;
//      string passwd;

        write("\n");
        old_pass=query_temp("ad_password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("您两次输入的管理密码并不一样，请重新设定一次管理密码：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        set("ad_password", old_pass, ob);
        check_ok(ob);
}

protected void check_ok(object ob)
{
        object user;
//      string *res;
//      string str,str1,str2;
        int /*   on,fee,i,*/ rec = 0;

        /*
        if( !BAN_D->vaild_allow_address(ob) ) {
                call_out("destruct_ob", 0, ob);
                return;
        }
        */
        // Check if we are already playing.
        user = find_body(query("id", ob));
        if( !objectp(user) )
                user = make_body(ob);
        else
                rec = 1;

        if( !objectp(user)) {
                write(HIR "无法创建该玩家，你可以尝试重新登录或是和巫师联系。\n" NOR);
                return ;
        }

        if( rec != 1 && !user->restore()) { // 必须要判断rec的值，否则会把玩家数据返回到前一次存储的数据
                write(HIR "无法读取该玩家数据，你可以尝试重新登录或是和巫师联系。\n" + rec + NOR);
                return ;
        }

#ifdef NO_FEE
        if( query_temp("tomud", ob) )
                write(ALERT("文字MUD游戏『"+LOCAL_MUD_NAME()+"』将永久免费开放！请新老玩家相互转告！\n"));
#else
        /*
        if( query("monfee", user)<time() && arrayp(res=query_temp("res", ob))){
                str1 = res[1] + "0";
                str2 = res[2] + "0";
                if( sscanf(str1, "%d", on) == 1 && sscanf(str2, "%d", fee) == 1 ) {
                        on /= 10;
                        fee /= 10;
                        i = onl / 3600;
                        str = "你总共购买游戏时间： " + fee + " 个小时$$" +
                              "你已经在游戏中进行了：" + i + "小时" + ((on % 3600) / 60) + "分钟$$";
                        if( i >= fee )
                                str += "你购买的游戏时间已经使用完了，请联系『王者歸來』小组继续购买游戏时间！$$游戏主页： http://www.mudzone.org $$";
                        else if( (fee - i) < 18 )
                                str+="你购买的游戏时间已经只有 " + (fee - i - 1) + " 小时多一点了$$请赶快去 http://www.mudzone.org 给你的帐号续费吧$$";
                        else if( fee == i )
                                str += "你购买的时间已经不到一个小时了，请尽快去 http://www.mudzone.org 给你的帐号续费$$";
                        if( fee == 18 )
                                str += NO_FEE_WARNING;
                        write(ALERT(str) + ((fee > 18) ? TMI("regur good") : "") + TMI("dlurl 123.12586.com/images/face32/"));
                        if( i >= fee ) {
                                call_out("destruct_ob", 0, ob);
                                call_out("destruct_ob", 0, user);
                                return;
                        }
                        // write(ALERT("a"));
                }
                // else
                //         write(ALERT("b"));
        }
        // else
        //write(ALERT("c")+"FLAG:"+query("monfee", user)+""+time()+""+arrayp(res=query_temp("res", ob)));

        // Check if we are already playing.
        // user = find_body(query("id", ob));
        // if( user ) {
        */
#endif

        if( rec ) {
                if( user->is_net_dead() ) {
                        reconnect(ob, user);
                        return;
                }
                write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        } else {
                mixed err;
                string msg;

                log_file("usage", sprintf("%s(%s) loggined from %s (%s)\n",
                        query("name", user),query("id", user),
                        query_ip_number(ob), ctime(time()) ) );

                if( query("last_on", ob)<time() &&
                    query("last_on", ob)>time()-30 &&
                    !wiz_level(user) ) {
                        write("你距上一次退出时间只有"+chinese_number(time()-query("last_on", ob))+
                              "秒钟，请稍候再登录。\n");
                        call_out("destruct_ob", 0, user);
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                set_temp("logon_time", time(), user);
                set("last_save", time(), user);
                if( err = catch(waiting_enter_world(ob, user)) ) {
                        set_temp("debug_msg", err, user);
                        msg = HIR "\n你无法进入这个世界，可能你的档案出了一些问题，需要和巫师联系。\n\n" NOR;
                        if( mapp(err) )
                                msg += MASTER_OB->standard_trace(err, 1);
                        set_temp("error", msg, user);
                        write(msg);
                }
                return;
        }
}

protected void confirm_relogin(string yn, object ob, object user)
{
        object old_link;

        if( !yn || yn=="" ) {
                write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("好吧，欢迎下次再来。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( user ) {
                tell_object(user, "有人从别处( " + query_ip_number(ob)
                                + " )连线取代你所控制的人物。\n");
                log_file("usage", sprintf("%s(%s) replaced by %s (%s)\n",
                         query("name", user),query("id", user),
                         query_ip_number(ob), ctime(time())));

                // Kick out tho old player.
                old_link=query_temp("link_ob", user);
                if( old_link ) {
                        exec(old_link, user);
                        call_out("destruct_ob", 0, old_link);
                }
        } else {
                write("在线玩家断开了连接，你需要重新登陆。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        reconnect(ob, user);
}

protected void confirm_id(string yn, object ob)
{
        if( yn=="" ) {
                write("使用这个名字将会创造一个新的人物，请问您确定吗("HIR"y"NOR"/"HIY"n"NOR")？");
                input_to("confirm_id", ob);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("好吧，那么请重新输入您的英文名字：");
                input_to("get_id", ob);
                return;
        }
        write(CLR);
        write("\n\n");
        write(HIW @TEXT

请输入您的高姓大名，由于这个名字代表你的人物，而且以后不能更
改，务必慎重择名（不雅观的姓名将被删除）。另：请不要选择金庸
小说中已有人物姓名。

首先输入的是你的姓，比如你想扮演角色叫张三，先输入“张”，然
后电脑会询问你的名字，那时你再输入“三”。如果你想扮演的角色
的名字比较怪，比如叫“老虎”，可以不输入姓，直接敲回车略过。
但是建议你还是输入一个比较像样子的姓名，而这些比较怪的称号可
以用昵称代替，否则某些地方的称呼可能会比较怪。如果你要加入世
家，那么你就不必输入姓了，因为一旦加入世家将自动选择家传祖姓，
不是你自己决定的。

TEXT NOR
        );
        write("您的中文" HIG "姓氏" NOR "(不要超过两个汉字)：\n");
        input_to("get_surname", ob);
}

protected void get_surname(string arg, object ob)
{
        if( arg && strlen(arg) > 0 ) {
                if( query_temp("big5", ob) )
#ifdef LONELY_IMPROVED
                        // arg = B2G(arg);
                        arg = LANGUAGE_D->toGB(arg);
#else
                        arg = LANGUAGE_D->toGB(arg);
#endif
                if( !check_legal_name(arg, 2) ) {
                        write("您的中文" HIG "姓氏" NOR "(不要超过两个汉字)：\n");
                        input_to("get_surname", ob);
                        return;
                }
                set("surname", arg, ob);
        } else {
                write("您的中文" HIG "姓氏" NOR "(不可以没有姓氏)：\n");
                input_to("get_surname", ob);
                return;
        }
        write("您的中文" HIY "名字" NOR "(不要超过两个汉字)：\n");
        input_to("get_name", ob);
}

protected void get_name(string arg, object ob)
{
        string fname;
        string result;

        if( query_temp("big5", ob) )
#ifdef LONELY_IMPROVED
                // arg = B2G(arg);
                arg = LANGUAGE_D->toGB(arg);
#else
                arg = LANGUAGE_D->toGB(arg);
#endif
        if( !check_legal_name(arg, 2) ) {
                write("您的中文" HIY "名字" NOR "(不要超过两个汉字)：\n");
                input_to("get_name", ob);
                return;
        }
        set("purename", arg, ob);

        fname=query("surname", ob);
        if( !stringp(fname) ) fname = "";
        fname += arg;

        if( strlen(fname) < 2) {
                write("对不起，你的中文名字（姓和名的组合）至少要有两个汉字。\n");
                write("\n请重新输入您中文" HIG "姓氏" NOR "：\n");
                input_to("get_surname", ob);
                return;
        }

        if( stringp(result = NAME_D->invalid_new_name(fname))
        ||  stringp(result = NAME_D->invalid_new_name(arg)) ) {
                write("对不起，" + result + "\n");
                write("\n请重新输入您中文" HIG "姓氏" NOR "：\n");
                input_to("get_surname", ob);
                return;
        }

#ifdef DB_SAVE
        if( DATABASE_D->db_find_user("name", fname) ||
            DATABASE_D->db_find_user("name", arg) ) {
                write("对不起，你的姓名和其他站玩家的姓名重复或类似！\n");
                write("\n请重新输入您中文" HIG "姓氏" NOR "：\n");
                input_to("get_surname", ob);
                return;
        }
#endif

        if( arg == query("surname", ob)){
                write(HIW "\n系统发现你输入的姓和名字相同，这样你的名字将是：“"
                      HIY + arg + arg + HIW "”。\n"
                      "你是否是因为不了解本系统而且没有仔细阅读前面的帮助而错误的输入\n"
                      "了你的姓名，如果是，请你重新连接并输入你的名字，否则请你输入一\n"
                      "遍你的全名，表明你的确想使用这个名字。\n\n" NOR);
                write("请输入您的全名(即姓和名字的组合)：\n");
                input_to("input_full_name", ob, arg + arg);
                return;
        }

        write(HIW "\n为了保证你的人物的安全，游戏要求你设置两个密码。一个是管理密\n"
              "码，这个密码可以在你遗失了普通密码时登录游戏，并用来修改普通\n"
              "密码。平时请使用普通密码登陆，避免过于频繁的使用管理密码以导\n"
              "致潜在的泄漏风险。\n\n" NOR);
        write("请设定您的管理密码：\n");
        input_to("new_ad_password", 1, ob);
}

protected void input_full_name(string arg, object ob, string fname)
{
        if( arg != fname ) {
                write(WHT "\n你输入的全名并不是你姓和名字的的组合，系统认为你开始没有理解输\n"
                      "入名字的要求，" HIR "请你仔细阅读所有提示的条款，不要自作聪明"
                      NOR WHT "。包括在\n"
                      "今后的游戏过程中请仔细阅读各种帮助和公告，避免因为自以为是而导\n"
                      "致浪费时间或是遭受不必要的损失。\n" NOR);
                confirm_id("Yes", ob);
                return;
        }
        write("\n请设定您的管理密码：\n");
        input_to("new_ad_password", 1, ob);
}

protected void new_ad_password(string pass, object ob)
{
        write("\n");
        if( strlen(pass) < 5 ) {
                write("管理密码的长度至少要五个字元，请重设您的管理密码：\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        set_temp("ad_password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
        set_temp("ad_password", crypt(pass,0), ob);
#endif

        write("请再输入一次您的管理密码，以确认您没记错：\n");
        input_to("confirm_ad_password", 1, ob);
}

protected void confirm_ad_password(string pass, object ob)
{
//      mapping my;
        string old_pass;
//      string passwd;

        write("\n");
        old_pass=query_temp("ad_password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("您两次输入的管理密码并不一样，请重新设定一次管理密码：\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

        set("ad_password", old_pass, ob);

        write(HIW "普通密码是你平时登录游戏时使用的，游戏中可以通过 PASSWD 命令\n"
              "来修改这个密码。\n\n" NOR);
        write("请输入你的普通密码：\n");
        input_to("new_password", 1, ob);
}

protected void new_password(string pass, object ob)
{
        string ad_pass;

        write("\n");
        if( strlen(pass) < 3 ) {
                write("密码的长度至少要三个字元，请重设您的密码：\n");
                input_to("new_password", 1, ob);
                return;
        }

        if( stringp(ad_pass=query("ad_password", ob)) &&
            crypt(pass, ad_pass) == ad_pass ) {
                write(HIR "请注意，为了安全起见，系统要求你的管理密码和普通密码不能相同。\n\n" NOR);
                write("请重新设置您的普通密码：\n");
                input_to("new_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        set_temp("password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
        set_temp("password", crypt(pass,0), ob);
#endif

        write("请再输入一次您的密码，以确认您没记错：\n");
        input_to("confirm_password", 1, ob);
}

protected void confirm_password(string pass, object ob)
{
//      mapping my;
        string old_pass;
//      string passwd;

        write("\n");
        old_pass=query_temp("password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("您两次输入的密码并不一样，请重新设定一次密码：\n");
                input_to("new_password", 1, ob);
                return;
        }

        set("password", old_pass, ob);
        if( query_temp("reset_password", ob)){
                // 这是用户修改自己的密码分支流程，不是创建
                // 用户分支，因此转移到 check_ok 函数继续执
                // 行。
                ob->save();
                check_ok(ob);
                return;
        }

        write("您要扮演男性(m)的角色或女性(f)的角色？\n");
        input_to("get_gender", ob);
}

protected void get_gender(string gender, object ob)
{
        object user;
        int id_tmp;
        string id_num;

        write("\n");
        if( gender == "" ) {
                write("您要扮演男性("HIG"m"NOR")的角色或女性("HIM"f"NOR")的角色？");
                input_to("get_gender", ob);
                return;
        }

        if( gender[0] == 'm' || gender[0] == 'M' )
                set_temp("gender", "男性", ob);
        else if( gender[0] == 'f' || gender[0] == 'F' )
                set_temp("gender", "女性", ob);
        else {
                write("对不起，您只能选择男性("HIG"m"NOR")或女性("HIM"f"NOR")的角色：");
                input_to("get_gender", ob);
                return;
        }
        if( find_body(query("id", ob)) ) {
                write(HIR "这个玩家现在已经登录到这个世界上了，请"
                      "退出重新连接。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
#ifdef DB_SAVE
        if( !DATABASE_D->query_db_status() )
                DATABASE_D->connect_to_database();

        if( DATABASE_D->db_find_user("id",query("id", ob))){
                write(HIR "\n这个玩家现在已经在其他站注册了，请退出重新连接。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
#endif
        set("body", USER_OB, ob);
        if( !objectp(user = make_body(ob)) ) {
                write(HIR "\n你无法登录这个新的人物，请重新选择。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
        set("str", 14, user);
        set("dex", 14, user);
        set("con", 14, user);
        set("int", 14, user);
        set("per", 20, user);
        set("kar", 20, user);
        set("gender",query_temp("gender",  ob), user);

        set("registered", 0, ob);
        set("registered", 0, user);
        log_file("usage", sprintf("%s(%s) was created from %s (%s)\n",
                          query("name", user),query("id", user),
                          query_ip_number(ob), ctime(time())));

        init_new_player(user);
        set_temp("newplayer", 1, user);
        waiting_enter_world(ob, user);
        write("\n");

        id_tmp = to_int(read_file(CONFIG_DIR + "reg_players", 1)) + 1;
        id_num = sprintf("%d", id_tmp);
        write_file(CONFIG_DIR + "reg_players", id_num, 1);
}

object make_body(object ob)
{
        string err;
        object user;

        if( !is_root(previous_object()) ){
                log_file("static/security",
                         sprintf("%s try to create player(%s) on %s.\n",
                                 (string)geteuid(previous_object()),
                                 query("id", ob),
                                 ctime(time())));
                write("你没有权限创建玩家。\n");
                return 0;
        }

        seteuid(getuid());
        user = new(USER_OB);
        if( !user ) {
                write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n");
                write(err+"\n");
                return 0;
        }
        seteuid(query("id", ob));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
        set("id",query("id",  ob), user);
        set("surname",query("surname",  ob), user);
        set("purename",query("purename",  ob), user);
        user->set_name(0, ({ query("id", ob) }));
        return user;
}

private void init_new_player(object user)
{
        set("title", "普通百姓", user);
        set("birthday", time(), user);
        set("potential", 100, user);
        set("food", (query("str", user) + 10) * 10, user);
        set("water", (query("str", user) + 10) * 10, user);
        //set("channels", ({"chat","rumor","new","stock","info","sos","bill","family"}), user);
        set("channels", CHANNEL_D->query_default_channel(user->query_id(1)), user);
        CHANNEL_D->register_channel(user, query("channels"));
        set("chann", (["sos":1,"tch":1,"auc":1]), user);//默认显示在主窗口的频道

        // 记录名字
        NAME_D->map_name(query("name", user), query("id", user));

        set("monfee", time()+8640000, user);
        //set("env/prompt", "time", user);
        set("env/wimpy", 60, user);
        // 标准暂存讯息
	set("msg/chat", 1, user);
	set("msg/rumor", 1, user);
	set("msg/tell", 1, user);
	set("msg/say", 1, user);
	set("msg/emotion", 1, user);
        set("msg/size", 100, user);
        set("level", 1, user);
        set("env/show_way", 1, user);
}

void waiting_enter_world(object ob, object user)
{
        string msg;

        if( !is_root(previous_object()) ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        set_temp("waiting_enter", 1, ob);//防止被销毁

        if( file_size(NOTICE) > 0 ) {
                msg  = BLINK "□  " NOR + WHT + CHINESE_MUD_NAME + NOR +
                       HIK "公怖栏                          " NOR +
                       HIK + TIME_D->replace_ctime(stat(NOTICE)[1]) + "\n" NOR;
                msg += HIK "_______________________________________________________________________________\n\n" NOR;
                msg += read_file(NOTICE);
                msg += HIK "_______________________________________________________________________________\n\n" NOR;
        } else {
                msg = terminal_colour(color_filter(read_file(NOTICE_MOTD)), ([
                        "MUD_NAME"      : CHINESE_MUD_NAME,
                        "ENGLISH_NAME"  : INTERMUD_MUD_NAME,
                        "MUDLIB_VERSION": MUDLIB_VERSION_NUMBER,
                        "MUDOS_VERSION" : __VERSION__ ,
                        "ARCH"          : __ARCH__,
                        "UPDATE"        : TIME_D->replace_ctime(stat(NOTICE_MOTD)[1]),
                ]));
        }

        write(msg);

        write(WHT "请输入任意键继续或 " HIR + WAITING_ENTER_TIME + NOR + WHT " 秒后自动进入游戏\n" NOR);
        set_temp("call_out_handle", call_out((:enter_world,ob,user,0,WAITING_ENTER_TIME:),1), ob);

        input_to( (: enter_world, ob, user, 0, 1 :) );
}

varargs void enter_world(object ob, object user, int silent, int timer, string arg)
{
        object cloth, shoe;
        string startroom;
//      string place,address;
//      string sql,ip_number;
        string msg;
//      string *ret;
        object login_ob, *users;
        mapping marry;
        mixed err;

        if( !is_root(previous_object()) ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        if( !ob || !user ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        if( timer && --timer ) {
#ifdef LONELY_IMPROVED
                remove_input_to(ob);
#endif
                write(TOTOP(1) + WHT "请输入任意键继续或 " HIR + timer + NOR + WHT " 秒后自动进入游戏\n" NOR);
                set_temp("call_out_handle", call_out((:enter_world,ob,user,silent,timer:),1), ob);
                input_to( (: enter_world, ob, user, silent, 1 :) );
                return;
        }

        set_temp("link_ob", ob, user);
        set_temp("body_ob", user, ob);
        set("registered",query("registered",  user), ob);
        delete_temp("waiting_enter", ob);

        if( intp(query_temp("call_out_handle", ob)) )
                remove_call_out(copy(query_temp("call_out_handle", ob)));

        delete_temp("call_out_handle", ob);
#ifdef LONELY_IMPROVED
        remove_input_to(ob);
#endif
        ob->clear_msg_buffer();

        //user->set_encoding(ob->query_encoding());
        if( query_temp("big5", ob) ) set_temp("big5", 1, user);
        if( query_temp("tomud", ob) ) set_temp("tomud", 1, user);

        if( query("last_on", ob)<time() &&
            query("last_on", ob)>time()-30 &&
            !wiz_level(user) ) {
                write("你距上一次退出时间只有"+chinese_number(time()-query("last_on", ob))+
                      "秒钟，请稍候再登录。\n");
                call_out("destruct_ob", 0, user);
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( interactive(ob) ) exec(user, ob);
        user->setup();

        if( query("age", ob) == 14 ) {
                set("food", user->max_food_capacity(), user);
                set("water", user->max_water_capacity(), user);
        }

#ifdef DB_SAVE
        if( query_temp("newplayer", user) && query("id", user) != "guest" ) {
                DATABASE_D->db_new_player(ob, user);
        }
#endif

#ifdef QUIT_SAVE_ALL
        if( query_temp("newplayer", user)){
                if( query("gender", user) == "女性"){
                        shoe = new("/clone/cloth/female-shoe.c");
                        cloth = new(sprintf("/clone/cloth/female%d-cloth.c", 1 + random(8)));
                } else {
                        shoe = new("/clone/cloth/male-shoe.c");
                        cloth = new(sprintf("/clone/cloth/male%d-cloth.c", 1 + random(8)));
                }
                cloth->move(user);
                //catch(cloth->wear());
                cloth->wear();
                shoe->move(user);
                //catch(shoe->wear());
                shoe->wear();
        } else {
                if( err = catch(user->restore_package()) ) {
                        set_temp("debug_msg", err, user);
                        write(HIR "\n你的身上物品档案出了一些问题，需要和巫师联系。\n\n" NOR);
                }
        }
#else
        if( !query_temp("newplayer", user)){
                if( err = catch(user->restore_package()) ) {
                        set_temp("debug_msg", err, user);
                        write(HIR "\n你的身上物品档案出了一些问题，需要和巫师联系。\n\n" NOR);
                }
        }
        if( wizhood(user) == "(player)" ) {
                if( query("class", user) == "bonze"){
                        if( query("gender", user) == "女性"){
                                cloth = new("/clone/cloth/ni-cloth.c");
                                shoe = new("/clone/cloth/ni-xie.c");
                        } else {
                                cloth = new("/clone/cloth/seng-cloth.c");
                                shoe = new("/clone/cloth/seng-xie.c");
                        }
                } else {
                        if( query("class", user) == "taoist"){
                                if( query("gender", user) == "女性"){
                                        cloth = new("/clone/cloth/daogu-cloth.c");
                                        shoe = new("/clone/cloth/dao-xie.c");
                                } else {
                                        cloth = new("/clone/cloth/dao-cloth.c");
                                        shoe = new("/clone/cloth/dao-xie.c");
                                }
                        } else {
                                if( query("gender", user) == "女性"){
                                        shoe = new("/clone/cloth/female-shoe.c");
                                        cloth = new(sprintf("/clone/cloth/female%d-cloth.c", 1 + random(8)));
                                } else {
                                        shoe = new("/clone/cloth/male-shoe.c");
                                        cloth = new(sprintf("/clone/cloth/male%d-cloth.c", 1 + random(8)));
                                }
                        }
                }
        } else {
                if( query("gender", user) == "女性"){
                        cloth = new("/clone/cloth/yunshang");
                } else {
                        cloth = new("/clone/cloth/jinduan");
                }
                shoe  = new("/clone/cloth/xianlv");
        }
        user->force_me("wear all"); // 其他下线不丢的防具先传上
        cloth->move(user);
        //catch(cloth->wear());
        cloth->wear();
        shoe->move(user);
        //catch(shoe->wear());
        shoe->wear();
        if( cloth && (!environment(cloth) || !query("equipped", cloth)) )
                destruct(cloth);
        if( shoe && (!environment(shoe) || !query("equipped", shoe)) )
                destruct(shoe);
#endif
        if( user->over_encumbranced() )
                write(HIY ">>>>>>>> 你已超重. <<<<<<<<\n" NOR );

        user->save();
        ob->save();

        UPDATE_D->check_user(user);

        if( !silent ) {
                write("\n\n");

                if( !query("registered", user)){
                        if( user->is_ghost() )
                                user->reincarnate();
                        set("startroom", REGISTER_ROOM, user);
                } else
                if( !stringp(query("born", user)) ) {
                        if( user->is_ghost() )
                                user->reincarnate();
                        set("startroom", BORN_ROOM, user);
                } else
                if( user->query_family() == "古村" ) {
                        if( user->is_ghost() )
                                user->reincarnate();
                        set("startroom", "/d/newbie/shijiezhishu", user);
                } else
                if( query("reborn_lunhui", user) || query("hell_quest", user) || query("over_quest/hell_quest", user) ) {
                        set("startroom", "/d/death/youmingdian", user);
                }

                if( (string)SECURITY_D->get_status(query("id", ob)) != "(player)" )
                        startroom = WIZARD_ROOM;
                else if( user->is_in_prison() )
                        startroom = user->query_prison();
                else if( user->is_ghost() )
                        startroom = DEATH_ROOM;
                else {
                        startroom=query("startroom", user);
                        if( !stringp(startroom)
                        ||  file_size(startroom + ".c") < 0
                        ||  startroom == CHAT_ROOM
                        ||  startroom == DEATH_ROOM )
                                startroom = START_ROOM;
                }

                if( !catch(load_object(startroom)) )
                        user->move(startroom);
                else {
                        startroom = START_ROOM;
                        user->move(startroom);
                        set("startroom", startroom, user);
                }

                if( !query("registered", user) )
                        write(color_filter(read_file(UNREG_MOTD)));
                else
                        write(color_filter(read_file(MOTD)));

                write("你连线进入" + MUD_NAME + "。\n");
                tell_room(startroom,query("name", user)+
                          "连线进入这个世界。\n", ({ user }));

#ifdef MCCP_SUPPORT
                if( !compressedp(user) )
                        write(YEL "你所使用的连线软体未启动网路传输压缩("
                              HIY "MCCP" NOR YEL ")功能，建议您启动该功能让网路更加顺畅。\n" NOR);
#endif
        }

        if( query("id", user) == "guest"){
                write(HIG "\n>>>>> 欢迎你来到这里参观。\n" NOR);
                user->guest_count();
        }

        login_ob = new(LOGIN_OB);
        set("id",query("id",  user), login_ob);
        login_ob->restore();
        if( !query("login_times", login_ob)){
                //write(NOR "你是第一次光临" + MUD_NAME + "。\n");
                write(HIG "\n>>>>> 欢迎你第一次来到这个世界！:)\n" NOR);
                set("login_times", 1, ob);
        // show rules
        } else {
                addn("login_times", 1, ob);
                write("你上次光临" + MUD_NAME + "是 " + HIG +
                        ctime(query("last_on", login_ob))+NOR+"从"+HIR+
                        query("last_from", login_ob)+NOR+"连接的。\n");
        }
        if( query_temp("newplayer", user) )
                CHANNEL_D->channel_broadcast("news", "新玩家 "+user->query_idname()+"-"+query("gender", user)+" 羞涩地进入了这个世界，一脸茫然的样子...。", 1);
        else if( query("last_on", login_ob) > 0 && time() - query("last_on", login_ob) > 7*86400 )
                CHANNEL_D->channel_broadcast("news", "阔别 "+((time()-query("last_on", login_ob))/86400)+" 天的玩家"+user->query_idname()+"再次进入了这个世界...", 1);

        destruct(login_ob);

        /*
        if( query_temp("no_allow_ip", ob) )
                write(HIR "警告：你未设定自己的登录地址范围。请用" HIY " allowip " HIR "指令设置。\n" NOR);
        */
// 暂时关闭
#ifdef DB_SAVE_BAK
        ip_number = resolve_ip_number(query_ip_number(user));
        sql = sprintf("SELECT place,address FROM %s WHERE ipstart <= \"%s\" AND"
                      " ipend >= \"%s\" ORDER BY ipend LIMIT 1", IP_TABLE,
                      ip_number, ip_number);
        if( sizeof(ret = DATABASE_D->db_fetch_row(sql)) )
        {
                place = ret[0];
                address = ret[1];
                msg = sprintf("%s(%s)由%s(%s，%s)连线进入。", user->name(), query("id", user), query_ip_number(user), place, address);
        }
        else
#endif
                msg = sprintf("%s(%s)由%s连线进入。", user->name(), query("id", user), query_ip_number(user));

        if( !(wizardp(user) && query("env/no_loginmsg", user)) )
                CHANNEL_D->do_channel(this_object(), "sys", msg);

#ifdef DB_SAVE
        DATABASE_D->db_set_player(query("id", user),"online",1);
        DATABASE_D->db_set_player(query("id", user),"last_station",LOCAL_STATION);
#endif

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(user);
#endif

       if( /*wizhood(user) != "(admin)" &&*/
           query("log_by/" + query("id", user), get_object(EXAMINE_D)) )
                user->start_log();

#ifdef DB_SAVE
        if( user->is_vip() && !BAN_D->is_netclub(query_ip_number(user)) )
#else
        if( BAN_D->is_welcome(query("id", user)) && !BAN_D->is_netclub(query_ip_number(user)) )
#endif
                BAN_D->open_club_line(user);    // 自动开放网吧限制

        // notice user the user of this mud
        NEWS_D->prompt_user(user);
        MSG_CMD->main(user, "system");
        ANALECTA_D->prompt_user(user);
        TOPTEN_D->topten_checkplayer(user);
        FESTIVAL_CMD->main(user);

        if( mapp(marry=query("couple", user)) && !undefinedp(marry["couple_id"])){
                string tmpstr, tmpstr1;
                object couple_ob = find_player(marry["couple_id"]);
                if( couple_ob ) {
                        if( query("gender", user) != "男性"){
                                tmpstr1 = "夫君";
                                tmpstr  = "爱妻";
                        } else {
                                tmpstr1 = "爱妻";
                                tmpstr  = "夫君";
                        }
                        write(sprintf(WHT HIM "\n你的%s%s已经在这等了你好久了，快去找%s吧。。。\n" NOR,
                                      tmpstr1, couple_ob->name(), gender_pronoun(query("gender", couple_ob))));
                        tell_object(couple_ob, sprintf(WHT HIM "\n你的%s%s抑制不住对你的思念跑来看你啦，快去和%s打个招呼吧。。。\n" NOR,
                                                       tmpstr,user->name(),gender_pronoun(query("gender", user))));
                }
        }

        if( (query("qi", user)<0 || query("jing", user)<0) && living(user) )
        {
                tell_object(user, HIR "你昏迷不醒人事！\n" NOR);
                user->unconcious();
        }

        if( !wizardp(user) || !query("env/invisible", user)){
                users = filter_array(users(), (: query_temp("tomud", $1) :));
                message("system", ADD2(user), users);
        }
        if( query_temp("tomud", user)){
                foreach( object player in users() )
                        tell_object(user, ADD2(player));
                user->force_me("inventory");
                user->force_me("wear all");
                user->force_me("cmdbar");
        }

           load_object("/u/redl/prison.c")->chk2_at_login(user);
}

varargs void reconnect(object ob, object user, int silent)
{
//      string sql,ip_number;
//      string place,address;
        string msg;
//      string *ret;
        int net_dead_time = query_temp("net_dead_time", user);
        string *msg_data = user->query_last_msg();

        set_temp("link_ob", ob, user);
        set_temp("body_ob", user, ob);
        if( query_temp("big5", ob) )
                set_temp("big5", 1, user);
        else
                delete_temp("big5", user);
        if( query_temp("tomud", ob) )
                set_temp("tomud", 1, user);
        else
                delete_temp("tomud", user);

        exec(user, ob);
        user->reconnect();

            //if( !silent && (!wizardp(user) || !query("env/invisible", user))){
            if( !silent && !query("env/invisible", user)){
                tell_room(environment(user),query("name", user)+YEL"重新连线回到这个世界。\n"NOR,
                ({user}));
        }

        if( query_temp("tomud", user)){
                user->force_me("look");
                user->force_me("inventory");
                user->force_me("cmdbar");
        }
#ifdef DB_SAVE_BAK
        DATABASE_D->db_set_player(query("id", user), "online", 1);

/*
        ip_number = resolve_ip_number(query_ip_number(user));
        sql = sprintf("SELECT place,address FROM %s WHERE ipstart <= \"%s\" AND"
                      " ipend >= \"%s\" ORDER BY ipend LIMIT 1", IP_TABLE,
                      ip_number, ip_number);
        if( sizeof(ret = DATABASE_D->db_fetch_row(sql)) )
        {
                place = ret[0];
                address = ret[1];
                msg = sprintf("%s(%s)由%s(%s，%s)重新连线进入。",query("name", user),query("id", user),query_ip_number(user),place,address);
        }
        else
*/
#endif
        msg = sprintf("%s(%s)由(%s)重新连线进入。",query("name", user),query("id", user),query_ip_number(user));
        CHANNEL_D->do_channel( this_object(), "sys", msg );

        if( net_dead_time )
                tell(user, YEL"\n"+pnoun(2, user)+"自断线于 " + ctime(net_dead_time) + " 到现在过了 " + ((time()-net_dead_time)/60) + " 分 " + ((time()-net_dead_time)%60) + " 秒。\n"NOR);

        if( sizeof(msg_data) && net_dead_time && to_int(msg_data[<3]) > net_dead_time )
                tell(user, HIY"\n在"+pnoun(2, user)+"断线的期间中有收到新的讯息，请使用 msg 指令查看。\n"NOR);
        delete_temp("net_dead_time", user);
}

int check_legal_id(string id)
{
        int i;
        i = strlen(id);

        if( (strlen(id) < 3) || (strlen(id) > 10 ) ) {
                write("对不起，你的"+HIW"英文"NOR+"名字必须是 3 到 10 个英文字母。\n");
                return 0;
        }

        if( member_array(id, banned_id) != -1 ) {
                write("对不起，" HIC"“" + id + "”" NOR"这个词有着特"
                      "殊的含意，不能用做英文名字。\n");
                return 0;
        }

        while(i--) {
                if( id[i]<'a' || id[i]>'z' ) {
                        write("对不起，你的"+HIW"英文"NOR+"名字只能用英文字母。\n");
                        return 0;
                }
        }
        return 1;
}

int check_legal_name(string name, int maxlen)
{
        int i;

        i = strlen(name);
        if( (strlen(name) < 1) || (strlen(name) > maxlen) ) {
                write("对不起，你的中文姓名不能太长或太短。\n");
                return 0;
        }

        if( !is_chinese(name) ) {
                write("对不起，请您用「中文」取名字。\n");
                return 0;
        }

        if( member_array(name, banned_name) != -1 ) {
                write("对不起，这种名字会造成其他人的困扰。\n");
                return 0;
        }

        //if( member_array(name, banned_name) % 2 == 0 )
        for( i=0; i<sizeof(banned_name); i++ ) {
                if( strsrch(name, banned_name[i]) != -1 ){
                        write("对不起，这种名字会造成其他人的困扰。\n");
                        return 0;
                }
        }
        return 1;
}

object find_body(string name)
{
        object ob, *body;

        if( objectp(ob = find_player(name)) )
                return ob;
        body = children(USER_OB);
        for( int i=0; i<sizeof(body); i++ ) {
                if( clonep(body[i]) &&
                    getuid(body[i]) == name ) {
                        if( !userp(body[i]) )
                                destruct(body[i]);
                        else    return body[i];
                }
        }
        return 0;
}

int set_wizlock(int level)
{
        if( wiz_level(this_player(1)) <= level )
                return 0;
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        wiz_lock_level = level;
        return 1;
}

int set_cruiselock(int level)
{
        if( wiz_level(this_player(1)) <= 4 )
                return 0;

        cruise_lock = level;
        return 1;
}

int set_madlock(int setmark)
{
        if( wiz_level(this_player(1)) < wiz_level("(arch)") )
                return 0;
        if( setmark == 1 ) mad_lock = 1;
        else    mad_lock = 0;
        return 1;
}

int get_madlock()
{
        return mad_lock;
}

int can_login(int level)
{
        if( level < wiz_lock_level )
                return 0;

        return 1;
}

int block_ip(string ip, int time, string reason)
{
        mapping tmp_ban = ([]);

        tmp_ban["reason"] = reason;
        tmp_ban["time"] = time();
        tmp_ban["punish"] = time;
        map_delete(blocks, ip);
        blocks[ip] = tmp_ban;

        return 1;
}

int unblock_ip(string ip)
{
        if( ip == "all" )
                blocks = ([]);
        else
                map_delete(blocks, ip);

        return 1;
}

mapping query_block()
{
        return blocks;
}
