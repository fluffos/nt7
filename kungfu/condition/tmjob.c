// tmjob.c

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if (duration < 1) return 0;
        
        me->apply_condition("tmjob", duration - 1);

        if (duration == 1)
        {
                delete_temp("started", me);
                delete_temp("asked", me);
                delete_temp("askok", me);
                delete_temp("lianyl", me);
                delete_temp("where", me);
                delete_temp("mingchen", me);
                set_temp("tmjob_failed", 1, me);
                tell_object(me, "你抓蚊子消耗的时间太长了，任务失败！\n");
                me->apply_condition("tmjob", 0);
                return 0;
        }

        // return CND_CONTINUE;      
        return 1;      
}

string query_type(object me) 
{
        return "job"; 
}