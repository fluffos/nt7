#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "风魔舞" NOR; }

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

        if (me->query_skill("yunzhou-fufa", 1) < 60)
                return notify_fail("你的云帚拂法级别不够，无法施展" + name() + "！\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不够，无法施展" + name() + "！\n");

        if (me->query_skill_mapped("whip") != "yunzhou-fufa")
                return notify_fail("你没有激发云帚拂法，无法施展" + name() + "！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "\n$N暴喝一声，潜运体内真气，将" + weapon->name() + HIY
              "挥舞得呼呼直响，直破长空，犹如漫天狂沙般卷向$n。\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "只觉风声萧萧，眼前万千鞭影，顿感"
                      "手脚无措，惊慌不已。\n" NOR;

                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                      CYN "的企图，斜跳躲闪开来。\n" NOR;
        }
        me->start_busy(1);

        addn("neili", -80, me);
        message_combatd(msg, me, target);

        return 1;
}