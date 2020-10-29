// haoran.c 浩然一击

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "浩然一击"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("浩然一击只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("haotian-zhang", 1) < 60)
                return notify_fail("你的昊天掌不够娴熟，不会使用浩然一击。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功修为不够，难以施展浩然一击。\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在真气不够，无法使用浩然一击。\n");

        if (me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("你现在没有激发昊天掌法，无法使用浩然一击。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必须空手才能够使用浩然一击。\n");

        msg = HIC "$N" HIC "大喝一声，合身向$n" HIC "扑上，双掌"
              "同时击出，正是一招「浩然一击」。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -110, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "结果$p" HIR "被$P" HIR "的气势所"
                                           "摄，慌忙后退，结果被$P" HIR "一掌击"
                                           "了个正中，吐血不止！！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -60, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}