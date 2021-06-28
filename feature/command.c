// This program is a part of NT MudLIB
// command.c

// #pragma optimize
// #pragma save_binary

#include <command.h>
#include <origin.h>

// Let command path be static, thus we can make sure no one can get command
// path directly from restore_object().
nosave string *path;
nosave int enabled = 0;
nosave int total_timecost = 0;

string *query_path() { return path; }
mixed *query_commands() { return commands(); }

nomask void set_path(string *p) { path = p; }

// Leave this to allow other objects can search your commands such as
// help, which...
string find_command(string verb)
{
        return (string)COMMAND_D->find_command(verb, path);
}

string remove_leading_space(string arg)
{
        int i;

        for( i = 0; i < strlen(arg); i++ )
                if( arg[i..i] != " " )
                        return arg[i..strlen(arg)];
        return "";
}

nomask int evaluate_command(string verb, string arg)
{
        string file;
        mapping para;
        object me = this_object();

#ifdef PROFILE_COMMANDS
        int mem, utime, stime;
        mapping info;

        mem = memory_info();
        info = rusage();
        utime = info["utime"];
        stime = info["stime"];
#endif

        para = me->query_entire_dbase();
        para = para["env"];
        /*
        if( mapp(para) && para["pure_say"] && !me->is_direct_command() )
        {
                if( stringp(file = find_command("say")) &&
                        call_other(file, "main", me, me->query_orginal_input()) )
                        return 1;
                else
                        return 0;
        }
        */

        if( !arg && (environment(me) &&
                stringp(query("exits/" + verb, environment(me)))) &&
                stringp(file = find_command("go")) && call_other(file, "main", me, verb) )
                ; else
        if( stringp(file = find_command(verb)) && call_other(file, "main", me, arg) )
                ; else
        if( me->is_in_prison() )
                return notify_fail("狱卒喝道：你老老实实的呆着别动！" + appromix_time(me->query_time_to_leave(), 1) + "放你出去！\n")
                ; else
        if( query("id") == "guest" )
                return notify_fail("既然仅仅是来参观，还是不要说话了！\n")
                ; else
        if( EMOTE_D->do_emote(me, verb, arg) )
                ; else
        if( CHANNEL_D->do_channel(me, verb, arg) )
                ; else
        if( mapp(para) && para["auto_say"] && query_fail_msg() == "什么？\n" &&
                stringp(file = find_command("say")) && !me->is_direct_command() &&
                call_other(file, "main", me, me->query_orginal_input()) )
                ; else
                return 0;

#ifdef PROFILE_COMMANDS
        info = rusage();
        PROFILE_D->log_command(verb, memory_info() - mem, info["stime"] - stime,
                info["utime"] - utime);
#endif
        return 1;
}

// This is the add_action hook handling movement, commands, emotes and
// channels. Optimization is needed.
protected nomask int command_hook(string arg)
{
        object me = this_object();
        string verb = query_verb();
//      int command_timecost;
        int result;

        if( !objectp(me) ) return 0;

        if( (verb = remove_leading_space(verb)) == "" )
                return 0;

        /*
#ifdef COUNT_COMMAND_TIMECOST
        command_timecost = time_expression
        {
                (result = evaluate_command(verb, arg));
        };
        if( !objectp(me) ) return 1;
        if( command_timecost > 200000 )
                CHANNEL_D->channel_broadcast("nch", sprintf("%s下达指令 %s 超过系统限制，执行时间(%fs) \n", me->query_idname(1), verb+ " " +arg, to_float(command_timecost)/1000000));
#else
        result = evaluate_command(verb, arg);
        if( !objectp(me) ) return 1;
        command_timecost = 100000;
#endif
        total_timecost += command_timecost;
        */

        result = COMMAND_D->evaluate_command(me, verb, arg, path);
        if( !objectp(me) ) return 1;

        return result;
}

int force_me(string cmd)
{
        int ret;

        if( !is_root(previous_object()) )
                return 0;

        ret = command(this_object()->process_input(cmd));
        if( objectp(this_object()) && !in_input() )
                this_object()->write_prompt();
        return ret;
}

nomask void enable_player()
{
        object me;
        string *my_path;

        if( stringp(query("id")) )
                set_living_name(query("id"));
        else if (stringp(query("name")))
                set_living_name(query("name"));

        /*
        if( query_temp("disable_input", this_object()) )
                delete_temp("disable_input", this_object());
        */

        if( !enabled ) {
                enable_commands(1);
                enabled = 1;
                // 由evaluate_command替代
                add_action("command_hook", "", 1);
        }

        me = this_object();
        if( !playerp(me) &&
            !interactive(me) &&
            !me->is_chatter() )
                my_path = NPC_PATH;
        else
        switch( wizhood(me) ) {
        case "(boss)":
        case "(admin)":
                my_path = ADM_PATH;
                enable_wizard();
                break;
        case "(arch)":
                my_path = ARC_PATH;
                enable_wizard();
                break;
        case "(wizard)":
                my_path = WIZ_PATH;
                enable_wizard();
                break;
        case "(apprentice)":
                my_path = APR_PATH;
                enable_wizard();
                break;
        case "(immortal)":
                my_path = IMM_PATH;
                enable_wizard();
                break;
        default:
                if( this_object()->is_in_prison() )
                        my_path = PNE_PATH;
                else
                        my_path = PLR_PATH;
        }

        if( me->is_chatter() )
                // remove skill cmds & usr cmds
                my_path -= ({ "/cmds/skill/", "/cmds/usr/" });

        set_path(my_path);
}

nomask void disable_player(string type)
{
//      object env;

        if( !is_root(previous_object()) &&
            previous_object() != this_object() ) return;

        set("disable_type", type);
        //set_temp("disable_input", 1);
        if (enabled)
        {
                disable_commands();
                enabled = 0;
        }

}

int add_total_timecost(int command_timecost)
{
        total_timecost += command_timecost;
}

int query_total_timecost()
{
        return total_timecost;
}
