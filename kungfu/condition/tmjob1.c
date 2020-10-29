// tmjob1.c

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if (duration < 1) return 0;
        
        me->apply_condition("tmjob1", duration - 1);

        if (duration == 1)
        {
                message_vision("$N一个纵身没有影了！\n", me);
                me->apply_condition("tmjob1", 0);
                destruct(me);
                return 0;
        }

        return 1;      
}

string query_type(object me) 
{
        return "job"; 
}