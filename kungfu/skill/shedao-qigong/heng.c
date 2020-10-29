// 唱仙法

#include <ansi.h>

string name() { return "哼字决"; }
int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("哼字决只能在战斗中使用。\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 80)
                return notify_fail("你的蛇岛奇功不够娴熟，不会使用哼子法。\n");

        if( query_temp("chang", me) <= -30 )
                return notify_fail("你已经哼得太久了，不能再哼了。\n");

        message_combatd(HIR "只听$N" HIR "口中念念有词，顷刻"
                        "之间内力大涨！\n" NOR, me);
        addn_temp("apply/attack", -10, me);
        addn_temp("apply/dodge", -10, me);
        addn_temp("apply/force", -10, me);
        addn_temp("apply/defense", -10, me);
        addn_temp("chang", -1, me);
        addn("neili", 1000, me);

        return 1;
}
