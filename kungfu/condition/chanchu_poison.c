// chanchu_poison.c
#include <ansi.h>

int update_condition(object me, int duration)
{
        if (me->is_ghost()) return 1;
        if( query_temp("nopoison", me))return 0;
        if( duration < 1 ) return 0;
        if (me->is_ghost())
        {
                me->clear_condition("chanchu_poison");
                return 0;
        }
        me->receive_wound("qi", 2500+random(2000));
        me->receive_damage("jing", 1500+random(2000));
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)
        {
                set_temp("die_reason", "蟾蜍毒发作而死", me);
                me->die();
                return 0;
        }
        me->apply_condition("chanchu_poison", duration - 1);
        tell_object(me, HIG"你觉得伤口一阵阵发凉，没啥感觉了。你中的蟾蜍毒发作了！\n" NOR );
        return 1;
}

string query_type(object me)
{
        return "poison";
}