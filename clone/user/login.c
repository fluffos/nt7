// login.c

#include <ansi.h>
#include <login.h>

inherit F_DBASE;
inherit F_SAVE;

void create()
{
        dbase = allocate_mapping(0);
        // 复制对象必须调用 LOGON 函数或者是设置连接身体
        // if (clonep()) call_out("time_out", 0);
}

void logon()
{
        remove_call_out("time_out");
        call_out("time_out", LOGIN_TIMEOUT);

        if( interactive(this_object()) )
                set_temp("ip_number", query_ip_number(this_object()));

        LOGIN_D->logon(this_object());
}

// Don't destruct(this_object()) in the net_dead() interactive apply or
// there'll be error message: Double call to remove_interactive()
void net_dead()
{
        remove_call_out("time_out");
        call_out( "time_out", 1);
}

void time_out()
{
        object body;

        if( query_temp("waiting_enter") )
                return;

        if( objectp(body = query_temp("body_ob")) ) {
                if( !environment(body) && !query("registered", body) )
                        destruct(body);
                return;
        }
        if( interactive(this_object()) )
                write("\n您花在连线进入手续的时间太久了，下次想好再来吧。\n");
        destruct(this_object());
}

// This is used by F_SAVE to determinethe file name to save our data.
string query_save_file()
{
        string id;

        id = query("id");
        if( !stringp(id) ) return 0;
        return sprintf(DATA_DIR "login/%c/%s", id[0], id);
}

nomask void catch_tell(string msg, string classes)
{
        if( query_temp("big5", this_object()) )
                msg = (string)LANGUAGE_D->toBig5(msg);

        while(strlen(msg) > 0) {
                receive(msg[0..__LARGEST_PRINTABLE_STRING__ - 1]);
                msg = msg[__LARGEST_PRINTABLE_STRING__..];
        }
}

nomask varargs void directly_receive(string msg)
{
        write(msg);
        /*
        while( strlen(msg ) > 0) {
                receive(msg[0..MAX_LAST_MSG - 1]);
                msg = msg[MAX_LAST_MSG..];
        }
        */
}

void receive_message(string type, string str)
{
        if( type!= "write" ) return;
        if( query_temp("big5", this_object()) )
                str = (string)LANGUAGE_D->toBig5(str);
        receive(str);
}

void terminal_type(string term_type)
{
        set_temp("terminal_type", term_type);
}

/*
void window_size(int width, int height)
{
        set_temp("window_size", ({width, height}));
}
*/
nomask void window_size(int width, int height)
{
        set("windowsize", ([
                "width":width,
                "height":height,
        ]));
}

string process_input(string str)
{
        if( query_temp("big5", this_object()) )
                str = LANGUAGE_D->Big52GB(str);
        return str;
}

int save()
{
        int res;

#ifdef DB_SAVE
        res = DATABASE_D->db_set_player(query("id"), "login_dbase",
                save_variable(query_entire_dbase()));
#endif
        if( TX_SAVE )
                res = ::save();

        return res;
}

int restore()
{
        int res = 0;

#ifdef DB_SAVE
        mapping dbase;
        string  str;

        str = DATABASE_D->db_query_player(query("id"), "login_dbase");
        if( str && stringp(str) ) {
                dbase = restore_variable(str);
                if( mapp(dbase) ) {
                        set_dbase(dbase);
                        res = 1;
                }
        }
#else
        if( TX_SAVE )
                res = ::restore();
#endif
        if( (int)query_temp("restore_mysql") )
                res = ::restore();

        return res;
}
