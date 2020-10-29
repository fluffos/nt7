// tmjob2.c

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if (duration < 1) return 0;
        
        me->apply_condition("tmjob2", duration - 1);

        if (duration == 1)
        {
                message_vision("$N蚊子嗡嗡的飞走消失了！\n", me);
                me->apply_condition("tmjob2", 0);
                destruct(me);
                return 0;
        }

        return 1;      
}

string query_type(object me) 
{
        return "job"; 
}