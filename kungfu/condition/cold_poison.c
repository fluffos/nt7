// cold_poison.c

#include <ansi.h>;
#include <condition.h>;
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if (me->is_ghost()) return 1;
        if( !living(me) || query_temp("noliving", me) )
        {
                message("vision", HIW+me->name()+"瑟瑟发抖，全身结上一层薄薄的白霜。\n"NOR, environment(me), me);
        }
        else {
                tell_object(me, HIW"忽然一股寒气优似冰箭，循着手臂，迅速无伦的射入胸膛，你中的寒毒发作了！\n"NOR);
                message("vision", HIW+me->name()+"全身发颤，牙关格格直响，过得片刻，嘴唇也紫了，脸色渐渐由青而白。\n"NOR, environment(me), me);
        }
        me->receive_damage("qi", 3500);
        if(userp(me)) me->receive_wound("jing", 2000);
        else me->receive_wound("jing", 4000);
        if(!me->is_busy()) me->start_busy(2);
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)
        {
                set_temp("die_reason", "体内寒毒发作而死", me);
                return 0;
        }
        me->apply_condition("cold_poison", duration - 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}