// hot_poison.c

#include <ansi.h>;
#include <condition.h>;
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if (me->is_ghost()) return 1;
        if( !living(me) || query_temp("noliving", me) )
        {
                message("vision",me->name()+"全身变黑，散发出一阵焦糊味。\n", environment(me), me);
        }
        else
        {
                tell_object(me,HIR"忽然一股火热之气袭来，烫得你手脚乱抖！\n"NOR);
                tell_room(environment(me),HIR+me->name()+"突然全身冒出阵阵红烟，嘴唇干裂，双手胡乱地挥舞着。\n"NOR, ({ me }));
        }
        me->receive_damage("qi", 2500);
        if(userp(me)) me->receive_wound("jing", 2000);
        else me->receive_wound("jing", 4000);
        if(!me->is_busy()) me->start_busy(2);
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)
        {
                set_temp("die_reason", "体内热毒发作死亡", me);
                return 0;
        }
        me->apply_condition("hot_poison", duration - 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}