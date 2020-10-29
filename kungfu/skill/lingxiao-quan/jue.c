#include <ansi.h>
#include <combat.h>

string name() { return HIW "凌宵总诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" + name() + "。\n");

        if ((int)me->query_skill("lingxiao-quan", 1) < 60)
                return notify_fail("你的凌霄拳法不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "lingxiao-quan")
                return notify_fail("你没有激发凌霄拳法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "lingxiao-quan")
                return notify_fail("你现在没有准备使用凌霄拳法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "只听$N" HIW "一声断喝，双拳聚力齐发，一式「凌霄总决」携"
              "着风雷之势轰向$n" HIW "！\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "结果$p" HIR "闪避不及，被$P" HIR
                                           "一拳正中面门，顿时口喷鲜血，几乎昏厥"
                                           "！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}