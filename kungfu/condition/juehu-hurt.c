#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{   
        int l_temp;
    
        set_temp("die_reason", "精元枯竭", me);
        if (random(10) >= 3)
        {
                if (! living(me))
                        message("vision", me->name() + "浑身一阵哆嗦，冷得牙齿[咯咯]响。\n", 
                                environment(me), me);
                else
                {
                        tell_object(me, HIB "你忽然感到体内精元流泄，头昏沉沉的。\n" NOR );
                        message("vision", me->name() + "突然两腿发软，两手抱成一团，冷得直发抖。\n",
                                environment(me), me);
                }
                
                l_temp = 50 - (int)me->query_skill("force", 1) / 20;
                if (l_temp < 10) l_temp = 10;
                addn("jing", -l_temp, me);
                
                if ((int)me->query_skill("force", 1) < 180)
                { 
                        me->receive_wound("jing", random(1));
                } 
        }
        me->apply_condition("juehu_hurt", duration - 1);
        
        if (duration < 1) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "hurt";
}