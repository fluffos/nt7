// This program is a part of NT MudLIB
// message.c
// Rewritten by Lonely@nitan.org

// #pragma save_binary

#include <ansi.h>
#include <name.h>

#define MAX_STRING_SIZE         8000
#define MAX_MSG_BUFFER          500
#define MAX_LAST_MSG            100

string *mail_log = ({});
nosave string *msg_log = ({});
nosave string *msg_buffer = ({});
nosave int written = 0;

// status of written
#define NONE                    0
#define PROMPT_WRITTEN          1
#define COMMAND_RCVD            2

nosave string log_in = 0;

int set_mail(string *data)
{
        mail_log = data;
        return 1;
}

string *query_mail() { return mail_log; }
int is_loging_now() { return log_in != 0; }

int start_log()
{
        string file;
        if( !is_root(previous_object()) ) return 0;

        if( log_in ) return 0;

        if( !(file = EXAMINE_D->create_log_file(this_object())) )
                return 0;

        log_file(file, sprintf("The system log the action of %s(%s) from %s on %s.\n\n",
                               name(1), query("id"),
                               query_ip_name(this_object()), ctime(time())));
        log_in = file;
        return 1;
}

void end_log()
{
        if( !log_in ) return;
        if( !is_root(previous_object()) ) return;

        log_file(log_in, sprintf("The system stop log at %s.\n\n",
                 ctime(time())));
        log_in = 0;
}

void log_command(string msg)
{
        if( !log_in ) return;

        log_file(log_in, HIC + ctime(time())[11..18] +
                         HIY "> " + msg + NOR "\n");
}

void log_message(string msg)
{
        if( !log_in ) return;

        msg = replace_string(msg, ESC "[256D" ESC "[K", "\n");
        msg = replace_string(msg, ESC "[1A", "");
        log_file(log_in, msg);
}

string prompt()
{
        string p;
        string prompt, path;
        mixed list;
        mapping my;

        if( arrayp(list = query_temp("tell_list")) &&
            sizeof(list) > 1 ) {
                if( !query_temp("tomud") )
                        p = HIG "> " NOR;
                else
                        p = HIG "<有信息>" NOR;
        } else {
                if( !query_temp("tomud") )
                        p = HIY "> " NOR;
                else
                        p = "";
        }
        if( !stringp(prompt = query("env/prompt")) )
                return "";

        switch( prompt ) {
        case "time":
                p = HIC + ctime(time())[11..18] + p;
                break;
        case "date":
                p = HIC + ctime(time())[0..9] + p;
                break;
        case "mud":
                p = HIC + NATURE_D->game_time() + p;
                break;
        case "hp":
                if( !query_temp("tomud") )
                        p = HIG + sprintf("%d/%d/%d", query("jing"), query("qi"), query("neili")) + p;
                else {
                        my = this_object()->query_entire_dbase();
                        p = TMI("statu " + sprintf("精%d气%d精力%d内力%d食%d水%d潜能%d经验%d",
                                my["jing"], my["qi"], my["jingli"], my["neili"],
                                my["food"], my["water"], my["potential"] - my["learned_points"],
                                my["combat_exp"]) + p);
                }
                break;
        case "path":
                if( !wizardp(this_object()) || wiz_level(this_object()) < 3 )
                        break;
                if( !stringp(path = query("cwd")) ) {
                        path = "/";
                        set("cwd", path);
                }
                // p = HIC + path[0..<2] + p;
                p = HIC + path[0..<2] + HIC "/ " NOR;
                break;
        default:
                p = prompt + p;
                break;
        }

        return p;
}

void receive_message(string msgclass, string msg)
{
        string subclass, *ch;
        object env;

        if( living(this_object()) && objectp(env = environment(this_object())) )
        {
                if( query("trans_msg_to", env) )
                        env->trans_message(msgclass, "\n"+NOR+HIR+"--==--\n"+HIR+">>|"+this_object()->query_idname()+"|<<\n"+NOR+msg+NOR+RED+"--==--\n\n"NOR);
        }

        if( !interactive(this_object()) ) {
                this_object()->relay_message(msgclass, msg);
                if( playerp(this_object()) ) this_object()->do_trigger(msg);
                return;
        }
        if( query_temp("big5") )
                msg = LANGUAGE_D->GB2Big5(msg);
        if( msgclass == "telnet" ) {
                receive(msg);
                return;
        }
        if( sscanf(msgclass, "%s:%s", subclass, msgclass) == 2 ) {
                switch( subclass ) {
                        case "channel":
                                //if( !pointerp(ch = query("channels"))
                                if( !pointerp(ch = CHANNEL_D->query_using_channel(this_object(), 1))
                                ||      member_array(msgclass, ch) == -1 )
                                        return;

                                if( query_temp("tomud") ) {
                                        if( !query("chann/" + msgclass))
                                                msg = PTEXT(msg);  // 默认往公共窗口扔频道信息
                                }
                                break;
                        case "outdoor":
                                if( !environment() || !query("outdoors", environment()) ) {
                                        if( query("env/look_window"))
                                                msg = HIG "【窗外景象】" +
                                                      NOR + msg;
                                        else
                                                return;
                                }
                                break;
                        case "system":
                                break;

                        default:
                                error("Message: Invalid Subclass " + subclass + ".\n");
                }
        }

        if( query_temp("block_msg/all")
        ||      query_temp("block_msg/" + msgclass) )
                return;

        if( in_input(this_object()) || in_edit(this_object()) ||
            this_object()->is_attach_system() && msgclass != "system" ) {
                if( sizeof(msg_buffer) > MAX_MSG_BUFFER )
                        msg_buffer = msg_buffer[1..];
                msg_buffer += ({ msg });
        } else {
                log_message(msg);
                if( written && !this_object()->is_attach_system() ) {
                        if( written == COMMAND_RCVD ) {
                                written = NONE;
                                if( !query_temp("tomud") )
                                        msg = ESC "[256D" ESC "[K" + msg;
                        } else {
                                if( !query_temp("tomud") )
                                        msg = ESC "[256D" ESC "[K" + msg + prompt();
                                else
                                        msg = msg + prompt();

                        }
                }
                while( strlen(msg) > MAX_STRING_SIZE ) {
                        receive(msg[0..MAX_STRING_SIZE - 1]);
                        msg = msg[MAX_STRING_SIZE..<1];
                }
                receive(msg);
        }
        if( userp(this_object()) ) this_object()->do_trigger(msg);
}

//
// 所有讯息输出的唯一通道, 支援 client 的讯息类别分类
//
/*
nomask varargs void catch_tell(string msg, string classes)
{
        string *ch;

        if( !msg || !msg[0] ) return;

        if( !interactive(this_object()) ) {
                this_object()->relay_message(classes, msg);
                if( playerp(this_object()) ) this_object()->do_trigger(msg);
                return;
        }
        if( query_temp("big5") )
                msg = LANGUAGE_D->GB2Big5(msg);
        if( classes == "telnet" ) {
                receive(msg);
                return;
        }

        if( stringp(classes) )
        {
                if( query_temp("tomud") )
                        if( !query("chann/" + classes))
                                msg = PTEXT(msg);  // 默认往公共窗口扔频道信息
        }

        if( query_temp("block_msg/all")
        ||      query_temp("block_msg/" + classes) )
                return;

        if( in_input(this_object()) || in_edit(this_object()) ||
            this_object()->is_attach_system() && classes != "system" ) {
                if( sizeof(msg_buffer) > MAX_MSG_BUFFER )
                        msg_buffer = msg_buffer[1..];
                msg_buffer += ({ msg });
        } else {
                log_message(msg);
                if( written && !this_object()->is_attach_system() ) {
                        if( written == COMMAND_RCVD ) {
                                written = NONE;
                                if( !query_temp("tomud") )
                                        msg = ESC "[256D" ESC "[K" + msg;
                        } else {
                                if( !query_temp("tomud") )
                                        msg = ESC "[256D" ESC "[K" + msg + prompt();
                                else
                                        msg = msg + prompt();

                        }
                }
                while( strlen(msg) > MAX_STRING_SIZE ) {
                        receive(msg[0..MAX_STRING_SIZE - 1]);
                        msg = msg[MAX_STRING_SIZE..<1];
                }
                receive(msg);
        }
        if( userp(this_object()) ) this_object()->do_trigger(msg);
}
*/

void clear_written()
{
        written = COMMAND_RCVD;
}

void clear_msg_buffer()
{
        msg_buffer = allocate(0);
}

int is_waiting_command()
{
        return (written == PROMPT_WRITTEN);
}

void write_prompt()
{
        string str;
        if( sizeof(msg_buffer) ) {
                receive(BOLD "[输入时暂存讯息]\n" NOR);
                for( int i = 0; i < sizeof(msg_buffer); i++ )
                        receive(msg_buffer[i]);
                msg_buffer = ({});
        }
        if( !living(this_object()) )
                return;
        str = prompt();
        if( this_object()->is_attach_system() )
                receive(HIR "执行中" HIY "> " NOR);
        else if( str ) {
                if( !this_object()->query_temp("tomud") )
                        receive(ESC "[256D" + str);
                else
                        receive(str);
        }
        written = PROMPT_WRITTEN;
}

void receive_snoop(string msg)
{
        object ob;

        if( (msg[0..5] == ESC "[256D") && (msg[6..8] != ESC "[K") )
                return;
        if( objectp(ob = query_snooping(this_object())) ) {
                if( query_temp("big5", ob) && !query_temp("big5") )
                        msg = LANGUAGE_D->Big52GB(msg);
                else if( !query_temp("big5", ob) && query_temp("big5") )
                        msg = LANGUAGE_D->GB2Big5(msg);
        }
        msg = replace_string(msg, ESC "[1A", "");
        msg = replace_string(msg, NOR, NOR BBLU WHT);
        // msg = replace_string(msg, ESC "[K", NOR ESC "[K" BBLU WHT);
        if( !query_temp("tomud") )
                msg = BBLU WHT + msg + NOR + " " + ESC "[1D";
        else
                msg = BBLU WHT + msg + NOR + " ";

        while( strlen(msg) > MAX_STRING_SIZE ) {
                receive(msg[0..MAX_STRING_SIZE - 1]);
                msg = msg[MAX_STRING_SIZE..<1];
        }
        receive(msg);
}

int is_mail_limit()
{
        if( !wizardp(this_object()) )
                return (sizeof(mail_log) > 50);
        else
                return (sizeof(mail_log) > 200);
}

string *query_msg_log()
{
        string *data;

        data = ({});
        if( arrayp(msg_log) && sizeof(msg_log) > 0 )
                data += msg_log;

        if( arrayp(mail_log) && sizeof(mail_log) > 0 )
                data += mail_log;

        return data;
}

string *query_last_msg()
{
        string *data;

        data = ({});
        if( arrayp(msg_log) && sizeof(msg_log) > 0 )
                data += msg_log;

        return data;
}

void add_msg_log(string type, string msg)
{
        if( !userp(this_object()) )
                return;

        if( type == "mail" ) {
                if( !arrayp(mail_log) ) mail_log = ({});
                if( !wizardp(this_object()) ) {
                        if( sizeof(mail_log) >= 60 )
                                mail_log = mail_log[3..] + ({ time(), type, msg });
                        else
                                mail_log += ({ time(), type, msg });
                } else {
                        if( sizeof(mail_log) >= 300 )
                                mail_log = mail_log[3..] + ({ time(), type, msg });
                        else
                                mail_log += ({ time(), type, msg });
                }
                return;
        }
        if( !query("msg/"+type) ) return;
        if( !wizardp(this_object()) ) {
                if( sizeof(msg_log)/3 >= (query("msg/size") || MAX_LAST_MSG) )
                        msg_log = msg_log[3..] + ({ time(), type, msg });
                else
                        msg_log += ({ time(), type, msg });
        } else {
                if( sizeof(msg_log)/3 >= (query("msg/size") || 20000 ) )
                        msg_log = msg_log[3..] + ({ time(), type, msg });
                else
                        msg_log += ({ time(), type, msg });
        }
}

void clear_msg_log()
{
        msg_log = allocate(0);
        mail_log = allocate(0);
}

nomask varargs void directly_receive(string msg)
{
        while(strlen(msg) > 0) {
                receive(msg[0..__LARGEST_PRINTABLE_STRING__ - 1]);
                msg = msg[__LARGEST_PRINTABLE_STRING__..];
        }
}
