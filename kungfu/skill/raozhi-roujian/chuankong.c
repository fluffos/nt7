// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "柔月穿空"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「柔月穿空」只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，使不出「柔月穿空」这一招！\n");

        if (me->query_skill("raozhi-roujian", 1) < 120)
                return notify_fail("你的绕指柔剑修为不够，使不出「柔月穿空」这一招！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真气不够，不能使用佛心剑！\n");

        msg = HIM "$N" HIM "猛地里一声清啸，剑法忽变，那柄" + weapon->name() + HIM
                  "竟似成了一条软带，轻柔曲折，飘忽不定，正是武当派的\n"
                  "七十二招「绕指柔剑」中的一招「柔月穿空」。只见$N"
                  HIM + weapon->name() + HIM "剑破长空，疾刺$n" HIM "胸膛，"
                  "剑到中途，\n剑尖微颤，竟然弯了过去，斜刺$p" HIM "右肩。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "结果$n" HIR "一个不慎，被$N" HIR
                                           "精妙的剑招刺中，一声惨嚎，鲜血飞溅而出！\n" NOR);
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "并不慌乱，收敛心神，轻轻格挡开了$P"
                       CYN "的剑招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
