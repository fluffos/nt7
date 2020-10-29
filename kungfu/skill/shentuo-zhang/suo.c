// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return CYN "雪锁千山" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;
        string *limbs, limb;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("shentuo-zhang", 1) < 150)
                return notify_fail("你神驼雪山掌火候不够，难以施展" +name()+ "。\n");

        if (me->query_skill_mapped("strike") != "shentuo-zhang")
                return notify_fail("你没有激发神驼雪山掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "shentuo-zhang")
                return notify_fail("你没有准备神驼雪山掌，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "一声冷笑，掌势一缓，一招「雪锁千山」，掌上阴劲如怒"
              "涛汹涌，缓缓推向$n。\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                pmsg = HIR "霎时只听「喀嚓」一声脆响，$n" HIR "的"
                        "胸口肋骨竟然断了几根。\n" NOR;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45, pmsg);

                me->start_busy(1);
                addn("neili", -50, me);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$P"
                       CYN "的企图，身形急动，躲开了这一掌。\n"NOR;
                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
