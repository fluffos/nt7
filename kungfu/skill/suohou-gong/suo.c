// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return CYN "铁爪锁喉" NOR; }

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        string *limbs, limb;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手施展。\n");

        if ((int)me->query_skill("suohou-gong", 1) < 150)
                return notify_fail("你琐喉功火候不够，难以施展"+name()+"。\n");

        if (me->query_skill_mapped("claw") != "suohou-gong")
                return notify_fail("你没有激发琐喉功，难以施展"+name()+"。\n");

        if (me->query_skill_prepared("claw") != "suohou-gong")
                return notify_fail("你没有准备琐喉功，难以施展"+name()+"。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不足，难以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "一声冷笑，蓦地拔地而起，右手一招「" NOR +
              CYN "铁爪锁喉" HIR "」直取$n" HIR "颈部。\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "claw");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;

                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "霎时只听「喀嚓」一声脆响，$N" HIR "五"
                               "指竟将$n" HIR "的喉结捏个粉碎。\n" NOR "("
                               " $n" RED "受伤过重，已经有如风中残烛，随时"
                               "都可能断气。" NOR ")\n";

                        damage = -1;
                        me->start_busy(1);
                        addn("neili", -50, me);

                } else
                {
                        target->start_busy(1 + random(3));

                        damage = damage_power(me, "claw");

                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75,
                                                   HIR "$n" HIR "慌忙躲闪，却听「喀嚓」一"
                                                   "声，$N" HIR "五指正拿中$n" HIR "的" +
                                                   limb + "。\n" NOR);
                        me->start_busy(3);
                        addn("neili", -180, me);
                }
        } else
        {
                msg += CYN "可是$n" CYN "看破了$P"
                       CYN "的企图，身形急动，躲开了这一抓。\n"NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}
