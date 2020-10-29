//
// cmd_d.c
//
// By Annihilator (11/07/94)
// Updated by Lonely

// #pragma optimize
// #pragma save_binary

#define COUNT_COMMAND_TIMECOST  1

mapping search = ([ ]);

void rehash(string dir)
{
        int i;
        string path;
        string *cmds;
        mapping cmdlist;
        string alias;

        if (! sscanf(dir, "/cmds/%s", path))
        {
                write("The path(" + dir + ")was not command path, "
                      "operation was failed.\n");
                return;
        }

        if (dir[sizeof(dir) - 1] != '/') dir += "/";
        cmds = get_dir(dir);
        i = sizeof(cmds);
        cmdlist = allocate_mapping(i);

        // 取所有命令
        while (i--)
                if (sscanf(cmds[i], "%s.c", cmds[i]))
                        cmdlist[cmds[i]] = dir + cmds[i] + ".c";

        // 取所有命令的别名
        i = sizeof(cmds);
        while (i--)
                if (sscanf(cmds[i], "%s.alias", cmds[i]))
                {
                        alias = read_file(dir + cmds[i] + ".alias", 1, 1);
                        alias = replace_string(alias, "\n", "");
                        alias = replace_string(alias, "\r", "");
                        sscanf(alias, "%s.c", alias);
                        if (member_array(alias, cmds) != -1)
                                cmdlist[cmds[i]] = dir + alias + ".c";
                }

        if (sizeof(cmds))
                search[dir] = cmdlist;
}

string find_command(string verb, string *path)
{
        int i;
        string file;
        mapping current;

        if (! pointerp(path)) return 0;

        for (i = 0; i < sizeof(path); i++)
        {
                if (undefinedp(current = search[path[i]]))
                {
                        rehash(path[i]);
                        if (undefinedp(current = search[path[i]]))
                                continue;
                }
                if (stringp(file = current[verb]))
                        return file;
        }
        return 0;
}

int do_command(object me, string verb, string arg, string *path)
{
        string file;
        mapping para;

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
                if( stringp(file = (string)find_command("say", path)) &&
                    call_other(file, "main", me, me->query_orginal_input()) )
                        return 1;
                else
                        return 0;
        }
        */

        if( !arg && (environment(me) &&
                stringp(query("exits/" + verb, environment(me)))) &&
                stringp(file = (string)find_command("go", path)) &&
                call_other(file, "main", me, verb) )
                ; else
        if( stringp(file = (string)find_command(verb, path)) &&
                call_other(file, "main", me, arg) )
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
                stringp(file = (string)find_command("say", path)) && !me->is_direct_command() &&
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

int evaluate_command(object me, string verb, string arg, string *path)
{
        int command_timecost;
        int result;

        if( !objectp(me) ) return 1;

#ifdef COUNT_COMMAND_TIMECOST
        command_timecost = time_expression
        {
                //(result = me->evaluate_command(verb, arg));
                (result = do_command(me, verb, arg, path));
        };
        if( !objectp(me) ) return 1;
        if( command_timecost > 200000 )
                CHANNEL_D->channel_broadcast("nch", sprintf("%s下达指令 %s 超过系统限制，执行时间(%fs) \n", me->query_idname(1), verb+ " " +arg, to_float(command_timecost)/1000000));
#else
        //result = me->evaluate_command(verb, arg);
        result = do_command(me, verb, arg, path);
        if( !objectp(me) ) return 1;
        command_timecost = 100000;
#endif
        me->add_total_timecost(command_timecost);
        return result;
}
