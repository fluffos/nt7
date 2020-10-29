// This program is a part of NITAN MudLIB
// huadu.c 化毒

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int i);

int exert(object me, object target)
{
        int skill, i;

        if( target != me || !target ) target = me;

        if ((int)me->query_skill("huagong-dafa", 1) < 50)
               return notify_fail("你的化功大法功火候太浅。\n");

        if ((int)me->query_skill("poison", 1) < 50)
               return notify_fail("你体内的毒素不够化毒所需。\n");


        if( query("neili", me)<800 )
                return notify_fail("你的内力不足于化毒。n");

        if( query("jing", me)<60 )
                return notify_fail("你的精神状态不足于化毒。\n");

        if( query_temp("huadu", me) )
                return notify_fail("你已运功化毒了。\n");

        skill = me->query_skill("force");
        addn("neili", 400, me);
        me->recieve_damage("jing", 50);

        message_combatd(BLU"$N闭目凝神，将体内蕴积的毒质慢慢化为真气，分散在四肢内。\n" NOR, me);
        i = me->query_skill("poison", 1) / 2;
        addn_temp("apply/attack", i, me);
        set_temp("huadu", 1, me);

        me->start_call_out((: call_other, this_object(), "remove_effect", me, i:), skill);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int i)
{
        if( query_temp("huadu", me) )
        {
                addn_temp("apply/attack", -i, me);
                delete_temp("huadu", me);
                message_combatd(BLU "$N运功化毒完毕，将真气化回毒质蕴积体内。\n" NOR, me);
        }
}