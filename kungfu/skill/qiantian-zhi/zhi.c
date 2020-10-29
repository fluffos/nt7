// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "乾阳神指" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("qiantian-zhi", 1) < 80)
                return notify_fail("你乾天指法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "qiantian-zhi")
                return notify_fail("你没有激发乾天指法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "qiantian-zhi")
                return notify_fail("你没有准备乾天指法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "陡然使出一招「乾阳神指」，双指齐施，同时朝$n"
              HIR "面门及胸口处点去。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");
                addn("neili", -80, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "结果$p" HIR "躲闪不及，登时被$P"
                                           HIR "一指点中，内息不由得一滞，难受之极。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}