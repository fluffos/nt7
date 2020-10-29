// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "打字诀"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int lvl;

        weapon=query_temp("weapon", me);

        if (! target)
                return notify_fail("你要打哪条蛇？\n");

        if (! target->is_snake())
                return notify_fail("看清楚些，那不是蛇，你瞎打什么？\n");

        if (! living(target))
                return notify_fail("那条蛇暂时不会动弹了，你不必再打了。\n");

        if ((int)me->query_skill("shedu-qiqiao", 1) < 20)
                return notify_fail("你的蛇毒奇巧还不够娴熟，不能打蛇。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的内功的修为不够，不能打蛇。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的内力不够了。\n");

        if (weapon)
                msg = HIC "\n$N" HIC "舞动手中的" + weapon->name() +
                      HIC "，朝着" + target->name() + HIC "的七寸打"
                      "了过去。\n" NOR;
        else
                msg = HIC "\n$N" HIC "伸出双指，出指如风，迅跻无比的"
                      "朝着" + target->name() + HIC "的七寸点了过去"
                      "。\n" NOR;

        lvl = (int) me->query_skill("shedu-qiqiao", 1) +
              (int) me->query_skill("dodge");
        lvl = lvl * lvl / 10 * lvl;

        if( lvl/2+random(lvl)<query("combat_exp", target) )
        {
                msg += HIY "结果只听“啪”的一声，正打在" + target->name() +
                       HIY "的七寸上。\n" NOR;
                lvl = (int) me->query_skill("force");
                lvl = lvl * 13 / 10;
                lvl = lvl * lvl / 10 * lvl;
//                if ( lvl / 2 + random(lvl) > (int) target->query("combat_exp") )
                if( lvl/2+random(lvl)<query("combat_exp", target) )
                {
                        msg += HIM "只见" + target->name() + HIM
                               "身子轻轻晃动几下，就不再动弹了。\n" NOR;
                        message_combatd(msg, me);
                        target->unconcious(me);
                } else
                {
                        msg += HIR + "哪里想到" + target->name() +
                               HIR "挨了这一击，竟然若无其事，顿时一个翻"
                               "身，直扑向$N" HIR "！\n\n" NOR;
                        message_combatd(msg, me);
                        target->kill_ob(me);
                }
        } else
        {
                msg += WHT "然而" + target->name() + WHT "身子一闪，躲了过去。\n\n" NOR;
                message_combatd(msg, me);
                target->kill_ob(me);
        }
        addn("neili", -50, me);
        me->start_busy(2);

        return 1;
}