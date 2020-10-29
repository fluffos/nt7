// by Lonely

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if( !me->is_fighting() && query_temp("hebi", me) )
        {
                int amount=query_temp("hebi_power", me);

                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("hebi", me);
                delete_temp("hebi_power", me);
                me->apply_condition("fanliangyi_check", 0);

                return 0;
        }
        else if( !query_temp("hebi", me) )
        {
                return 0;
        }
        else 
        {               
                return CND_CONTINUE;
        }       
}