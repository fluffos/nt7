// powerup.c 红花神功加力
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( target != me )
                return notify_fail("你只能用红花神功来提升自己的战斗力。\n");
        if( query("neili", me)<150 )
                return notify_fail("你的内力不够。\n");
        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        message_combatd(HIR"$N默默提起丹田之力，但觉全身暖洋洋的气息向上聚集，脸色也越来越红。猛地一声低吼，不怒自威。\n"NOR,me);
        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        set_temp("powerup", 1, me);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill/3:), skill);
        if( me->is_fighting() ) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/dodge", -amount, me);
        delete_temp("powerup", me);
        tell_object(me, "你的红花神功运行完毕，将内力收回丹田。\n");
}

int help(object me)
{
        write(WHT"\n红花神功之加力："NOR"\n");
        write(@HELP

        使用功效：
                提升自己的攻击防御能力

        出手要求：
                内力150
HELP
        );
        return 1;
}