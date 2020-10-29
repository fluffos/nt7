// This program is a part of NT MudLIB
// do.c chain-command

inherit F_CLEAN_UP;

#define MAX_DO_COMMANDS 15

int main(object me, string arg)
{
        int do_times;
        int total_cmds;

        if( !arg || arg == "" )
                return notify_fail("请输入要连续下达的指令。\n");

        if( query_temp("do_chain", me) )
                return notify_fail("系统在处理你的串连指令！\n");

        set_temp("do_chain", 1, me);
        foreach( string action in explode(arg, ",") )
        {
                do_times = 1;
                sscanf(action, "%d %s", do_times, action);

                if( do_times > MAX_DO_COMMANDS ) do_times = MAX_DO_COMMANDS;

                if( !strsrch(action, "do ") )
                {
                        delete_temp("do_chain", me);
                        tell_object(this_object(), "指令 do 中不能再有 do 的指令。\n");
                        return 1;
                }

                while( do_times-- && ++total_cmds )
                {
                        if( total_cmds > MAX_DO_COMMANDS && !wizardp(this_object()) )
                        {
                                delete_temp("do_chain", me);
                                tell_object(this_object(), "你不能一次下超过 "+MAX_DO_COMMANDS+" 个指令。\n");
                                return 1;
                        }
                        me->command(me->process_input(action));
                }
        }
        delete_temp("do_chain", me);
        return 1;
}

int help(object me)
{
        write( @HELP
指令格式: do <串连指令>

这个指令可以让你一次把一串指令交给伺服器处理，如此网路
封包将从多封包被压缩成单封包。
串连指令范例：
(六封包)原 ZMUD 多封包: e;s;s;enter door;kill liu mang;perform cuff.ji
(一封包)使用 do 单封包: do e,s,s,enter door,kill liu mang,perform cuff.ji

HELP );
        MYGIFT_D->check_mygift(me, "newbie_mygift/do");
        return 1;
}


