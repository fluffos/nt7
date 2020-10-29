#include <ansi.h>

string name() { return HIG "空明若玄" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int level;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((level = me->query_skill("kongming-quan", 1)) < 100)
                return notify_fail("你的空明拳不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "kongming-quan")
                return notify_fail("你没有激发空明拳，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "kongming-quan")
                return notify_fail("你没有准备空明拳，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气太弱，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "使出空明拳「" HIG "空明若玄" NOR + WHT "」，双手"
              "吞吐不定，运转如意，试图扰乱$n" WHT "的攻势。\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "结果$n" HIR "被$N" HIR "的拳招所牵制，招架"
                       "不迭，全然无法反击！\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企图，镇定逾"
                       "恒，全神应对自如。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
