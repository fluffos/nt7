#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        object where, cloth;
        where = environment(me);

        if(explode(base_name(where), "/")[0] != "d") return 0;
        if(explode(base_name(where), "/")[2] != "bhd") return 0;

        if( !(query("outdoors", where)))return CND_CONTINUE;
        if( objectp(cloth=query_temp("armor/cloth", me)) && query("warm_cloth", cloth))return 0;
        tell_object(me, HIR"忽然一阵刺骨的寒风袭来，你不禁打了个哆嗦！\n"NOR);             
        me->receive_damage("qi", 25);
        me->receive_wound("qi", 5);
        me->receive_damage("jing", 25);
        if( query("neili", me)>50 )
                addn("neili", -50, me);
        me->apply_condition("cold_wind", 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "weather";
}