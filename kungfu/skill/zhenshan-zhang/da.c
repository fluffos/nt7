// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "隔山打牛"; }

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("隔山打牛只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用隔山打牛！\n");

        if ((int)me->query_skill("zhenshan-zhang", 1) < 60)
                return notify_fail("你的震山掌不够娴熟，不会使用隔山打牛。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的内功修为不足，无法施展隔山打牛。\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在真气太弱，无法施展隔山打牛。\n");

        msg = WHT "$N" WHT "脚蹲马步，深吸一口气，使出隔山打牛，双掌对准$n"
              WHT "平平推出。\n" NOR;
        addn("neili", -100, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 50,
                                           HIR "$n" HIR "见势连忙向后一纵，结果只感"
                                           "胸口一震，顿时两耳轰鸣，原被$N" HIR
                                           "的内劲所伤！\n"
                                           ":内伤@?");
                if (! target->is_busy())
                        target->start_busy(3 + random(2));
                me->start_busy(2);
        } else
        {
                me->start_busy(2);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企图，并没有上当。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}