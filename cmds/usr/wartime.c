// time.c                                          
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int cur_time = time();  

        if( !wizardp(me) && cur_time-query_temp("last_who", me)<5 )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  

        set_temp("last_who", cur_time, me);
        if (! objectp(WAR_D->query_marshal()))
                return notify_fail("现在前方没有战事！\n"); 

        write(sprintf("王朝战争已经进行了" + WAR_D->query_continue_time() + "。\n"));
        return 1;
}

int help(object me)
{
     write(@HELP
指令格式: time

这个指令告诉你王朝战争已经进行的时间。

HELP
    );
    return 1;
}