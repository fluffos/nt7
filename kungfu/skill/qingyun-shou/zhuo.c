// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return WHT "捕风捉影" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("qingyun-shou", 1) < 50)
                return notify_fail("你的青云手不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("hand") != "qingyun-shou")
                return notify_fail("你没有激发青云手，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("hand") != "qingyun-shou")
                return notify_fail("你现在没有准备使用青云手，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "划身错步，单手拂过，手影虚虚实实，难辨真伪，完"
              "全笼罩$n" WHT "。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "hand");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "$p" HIR "一时辨别不清虚实，被$P"
                                           HIR "手影划过气门，气血翻滚，几乎窒息。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
