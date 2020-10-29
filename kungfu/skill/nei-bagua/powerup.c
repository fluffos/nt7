// powerup.c 内八卦神功加力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用内八卦神功来提升自己的战斗力。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的内力不够。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        message_combatd(HIY "$N" HIY "凝神聚气，运起内八卦神功，真气顿时灌满"
                        "全身，衣衫欲裂，气势磅礴。\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        addn_temp("apply/parry", skill/6, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect",
                               me, skill :), skill);

        if (me->is_fighting())
                       me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -(amount/3), me);
                addn_temp("apply/defense", -(amount/3), me);
                addn_temp("apply/parry", -(amount/6), me);
                delete_temp("powerup", me);
                tell_object(me, "你的内八卦神功运行完毕，将内力收回丹田。\n");
        }
}