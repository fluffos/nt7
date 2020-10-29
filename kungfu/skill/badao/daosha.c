#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill;
        object weapon;
        
        if( query("neili", me)<600 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("badao", 1) < 500)
                return notify_fail("你的霸刀修为不够。\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你还没有激发霸刀呢。\n");
                
        if( query_temp("badao-dasha", me) )
                return notify_fail("你已经施展起刀煞了。\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对！\n");
                
        skill = me->query_skill("badao", 1);
        addn("neili", -500, me);

        message_combatd(HIY "$N挥动起手中" + weapon->name() + HIY "，一股强劲的气流自全身涌向" + weapon->name() + 
                        HIY "，顿时，刀气四溢，杀气腾腾。\n" NOR, me);

        addn_temp("apply/damage", skill/2, me);
        set_temp("badao-dasha", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("badao-dasha", me) )
        {
                addn_temp("apply/damage", -(amount/2), me);
                delete_temp("badao-dasha", me);
                tell_object(me, "你的霸刀运行完毕，将内力收回丹田。\n");
        }
}