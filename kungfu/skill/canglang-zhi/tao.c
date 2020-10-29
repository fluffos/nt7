#include <ansi.h>
#include <combat.h>

string name() { return HIG "碧浪滔天" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("canglang-zhi", 1) < 80)
                return notify_fail("你沧浪指法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "canglang-zhi")
                return notify_fail("你没有激发沧浪指法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "canglang-zhi")
                return notify_fail("你没有准备沧浪指法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "陡然施出一势「碧浪滔天」，十指纷翻，指气嗤然作"
              "响，全全笼罩$n" HIG "。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");
                addn("neili", -80, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "结果$n" HIR "躲闪不及，被$N" HIR
                                           "一指命中，全身气血翻腾不已。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "可是$n" CYN "识破了$N"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}