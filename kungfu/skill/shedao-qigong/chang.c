// 唱仙法

#include <ansi.h>

string name() { return "唱字决"; }

int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("唱仙法只能在战斗中使用。\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 60)
                return notify_fail("你的蛇岛奇功不够娴熟，不会使用唱仙法。\n");

        if( query("neili", me)<300 )
                return notify_fail("你已经唱得精疲力竭，内力不够了。\n");

        if( query_temp("chang", me) >= 30 )
                return notify_fail("你已经唱得太久了，不能再唱了。\n");

        skill = me->query_skill("force");

        addn("neili", -200, me);

        message_combatd(HIR "只听$N" HIR "口中念念有词，顷刻"
                        "之间武功大进！\n" NOR, me);

        addn_temp("apply/attack", 10, me);
        addn_temp("apply/dodge", 10, me);
        addn_temp("apply/force", 10, me);
        addn_temp("apply/defense", 10, me);
        addn_temp("chang", 1, me);

        return 1;
}