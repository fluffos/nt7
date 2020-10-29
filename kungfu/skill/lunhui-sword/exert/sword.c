
#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        object weapon;

        if (target != me)
                return notify_fail("你只能用六道轮回剑来提升自己的战斗力。\n");

        if( query_temp("sword", me) )
                return notify_fail("你已经在运功中了。\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你还没有激发六道轮回剑为剑法，无法运功。\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你还没有装备上你的宝剑，无法运功。\n");
                
        skill = me->query_skill("force");
        
        if( query("neili", me)<3000 )
                return notify_fail("你内力不足，无法运功。\n");
                
        addn("neiil", -3000, me);
        
        message_combatd(NOR + CYN "$N轻转手中" + weapon->name() + NOR + CYN "，顷刻间，只见" + weapon->name() + 
                        NOR + CYN "被一道吞吐不定的青芒所笼罩，甚是奇异！\n\n" NOR, me);

        // 打通BREAKUP后的效果增加20%
        if( query("breakup", me))skill=skill+skill*2/10;

        addn_temp("apply/damage", skill/4, me);
        addn_temp("apply/sword", skill/8, me);
        set_temp("sword", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill / 10);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))return;

        if( query_temp("sword", me) )
        {
                addn_temp("apply/damage", -amount/4, me);
                addn_temp("apply/sword", -amount/8, me);

                delete_temp("sword", me);
                tell_object(me, HIW "你的六道轮回剑「轮回剑气」运行完毕，将内力收回丹田。\n" NOR);
        }


}