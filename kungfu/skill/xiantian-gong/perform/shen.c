// This program is a part of NITAN MudLIB
// shentong.c 先天功 纯阳神通功

// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "纯阳神通功" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;
        int delta;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 240)
                return notify_fail("你的先天功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你没有激发先天功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你没有激发先天功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("你没有准备使用先天功，难以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "运起纯阳神通功，片刻便见白气逐渐笼罩全身，双眼精光四射，与平时判若两人。\n"
              HIW "$N" HIW "接着突然出掌攻向$n，当真是无声无息，却迅如闪电。\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        delta = ABILITY_D->check_ability(me, "ap_power-xtg-shen"); // 门派ab
        if( delta ) ap += ap*delta/100;
        ap *=2;
        if (ap / 2 + random(ap*2) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        addn("neili", -800, me);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        damage*=5;
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 400,
                               HIR "$n" HIR "来不及反应，即被$N纯阳神通功惊人神功击中。\n" NOR "( $n"
                               RED "受伤过重，已经有如风中残烛，随时都可能断气"
                               "。" NOR ")\n" NOR);
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        damage*=4;
                        delta = ABILITY_D->check_ability(me, "da_power-xtg-shen"); // 门派ab
                        if( delta ) damage += damage*delta/100;
                        addn("neili", -500, me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300,
                                                   HIR "结果$N" HIR "纯阳神通功正中$n" HIR "胸"
                                                   "口，纯阳神通功登时透胸而入，$n" HIR "接连喷出数"
                                                   "口鲜血。\n" NOR);
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -120, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，但却很狼狈的躲避开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}
