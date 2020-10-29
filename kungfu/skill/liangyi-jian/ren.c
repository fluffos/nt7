#include <ansi.h>
#include <combat.h>

#define REN "「" HIW "天地同仁" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(REN "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" REN "。\n");

        if ((int)me->query_skill("liangyi-jian", 1) < 120)
                return notify_fail("你两仪剑法不够娴熟，难以施展" REN "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为不足，难以施展" REN "。\n");

        if (me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("你没有激发两仪剑法，难以施展" REN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，难以施展" REN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "手中长剑剑芒跃动，剑光暴长，剑尖颤动似乎分左右刺向$n"
              HIW "，$n" HIW "看到剑\n光偏左，疾侧身右转，但只这一刹，剑光刹时袭"
              "向右首！\n";

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "疾忙左转，却发现$N" HIR
                                           "的" + weapon->name() + HIR "疾往左转"
                                           "，登时穿胸而过，血如泉涌。\n" NOR);
                addn("neili", -180, me);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "轻轻一笑，侧身右转，躲开了$P"
                       CYN "左转的剑式，毫发未伤。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}