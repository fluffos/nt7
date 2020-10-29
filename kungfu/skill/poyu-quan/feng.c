// This program is a part of NITAN MudLIB
// feng.c 破玉拳「封闭手」

#include <ansi.h>

string name() { return HIG "封闭手" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if ((int)me->query_skill("poyu-quan", 1) < 60)
                return notify_fail("你的劈石破玉拳不够娴熟，不会使用" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "poyu-quan")
                return notify_fail("你没有准备使用劈石破玉拳，无法施展" + name() + "。\n");

        if( query("neili", me)<80 )
                return notify_fail("你现在真气不够，无法施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "\n只见$N" HIC "左掌虚探，右拳飕的一声从掌风中\n"
              "猛穿过来，正是劈石破玉拳法的绝招之一「" HIG "封闭手" HIC "」。\n" NOR;

        addn("neili", -40, me);
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果$p" HIR "运力招架，一时却觉得"
                       "内力不济，被$P" HIR "抢住手腕一拉，顿时立足"
                       "不稳，滴溜溜打了两个圈子。\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "奋力一架，硬生生格开了$P"
                       CYN "这一拳。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
