// 神龙再现

#include <ansi.h>

int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("龙形唱仙只能在战斗中使用。\n");

        if ((int)me->query_skill("hunyuan-yiqi", 1) < 150)
                return notify_fail("你的心意气混元功不够娴熟，不会使用龙形唱仙。\n");

        if( query("neili", me)<300 )
                return notify_fail("你已经精疲力竭，内力不够了。\n");

        if( query_temp("chang", me) >= 100 )
                return notify_fail("你已经叫得太久了，神龙已经厌倦了。\n");

        addn("neili", -100, me);

        message_combatd(HIR "只听$N" HIR "口中念念有词，神龙从天而将，"
                        "钻入$N体中！\n" NOR, me);

        addn_temp("apply/attack", 1, me);
        addn_temp("apply/dodge", 1, me);
        addn_temp("apply/defense", 1, me);
                addn_temp("apply/armor", 1, me);
                addn_temp("apply/damage", 1, me);
        addn_temp("chang", 1, me);

        return 1;
}
