// This program is a part of NITAN MudLIB
// fugu.c 金蛇游身掌-附骨缠身

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("附骨缠身只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你不是空手，不能使用附骨缠身。\n");

        if ((int)me->query_skill("jinshe-zhang", 1) < 100)
                return notify_fail("你的金蛇掌不够娴熟，不会使用附骨缠身。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在内力太弱，不能使用附骨缠身。\n");

        if (me->query_skill_prepared("strike") != "jinshe-zhang")
                return notify_fail("你现在没有准备金蛇掌法，无法使用附骨缠身。\n");

        msg = HIC "$N" HIC "大喝一声，缠身而上左手一探刁住$n"
              HIC "手腕，右掌猛下杀手！\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");
             
        if (target->is_busy() ||
            (ap / 2 + random(ap)) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
                COMBAT_D->do_attack(me, target, 0, 0);
                COMBAT_D->do_attack(me, target, 0, 0);

                addn("neili", -150, me);
                me->start_busy(2);
                msg = HIR "结果$n" HIR "被$N" HIR "的左手所制，"
                      "在「附骨缠身」下，一时竟然无法还手！\n" NOR;
        }
        else
        {
                me->start_busy(2);
                msg = CYN "可是$p" CYN "识破了$P"
                      CYN "这一招，手肘一送，摆脱了对方控制。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
