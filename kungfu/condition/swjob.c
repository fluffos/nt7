// swjob.c

#include <ansi.h>
#include <condition.h> 

int update_condition(object me, int duration)
{
        if( duration<1 && query_temp("defend_quest", me) )
        {
                tell_object(me, HIY "你的守卫门派任务结束。\n" NOR);
                set_temp("defend_quest/finish", 1, me);
                return 0;
        }
        if (! duration) return 0;
        me->apply_condition("swjob", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "job";
}