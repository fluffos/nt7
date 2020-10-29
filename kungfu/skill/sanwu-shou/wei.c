#include <ansi.h>

inherit F_SSERVER;

string name() { return HIG "无所不为" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放"
                                   "胆攻击吧。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你的武器不对，无法施展" + name() + "\n");

        if (me->query_skill("sanwu-shou", 1) < 70)
                return notify_fail("你的三无三不手级别不够，无法施展" + name() + "！\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不够，无法施展" + name() + "！\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("你没有激发三无三不手，无法施展 " + name() + "！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "\n$N暴喝一声，潜运体内真气，施出绝招「" HIG "无所不为" HIY
              "」将" + weapon->name() + HIY "挥舞得呼呼直响，\n忽左忽右，将$n"
              HIY "笼罩在" + weapon->name() + "的攻势之下。" NOR;
        me->start_busy(2);

        message_combatd(msg, me, target);

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if( ap / 2 + random(ap) > dp )
        {
                msg = HIR "$n" HIR "只觉风声萧萧，眼前万千鞭影，顿感"
                      "手脚无措，惊慌不已。\n" NOR;
                target->start_busy((int)me->query_skill("sanwu-shou") / 90 + 2);
        } else
        {
                msg = CYN "可是$p" CYN "看破了$P"
                      CYN "的企图，斜跳躲闪开来。\n" NOR;
        }
        addn("neili", -80, me);
        message_combatd(msg, me, target);

        return 1;
}