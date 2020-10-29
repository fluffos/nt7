// qing.c 清思剑

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "清思剑"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「清思剑」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("tianyu-qijian", 1) < 70)
                return notify_fail("你的天羽奇剑不够娴熟，不会使用。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功实在太差，没法用「清思剑」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在内力太弱，不能使用「清思剑」。\n");

        if (me->query_skill_mapped("sword") != "tianyu-qijian")
                return notify_fail("你没有激发天羽奇剑，没法用「清思剑」。\n");

        msg = HIG "$N" HIG "手腕轻轻一抖，手中的" + weapon->name() +
              HIG "化作一道彩虹，光华眩目，笼罩了$n" HIG "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);

                addn("neili", -120, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "只见$N" HIR "剑花聚为一线，穿向$n"
                                           HIR "，$p" HIR "只觉一股热流穿心而过，"
                                           "喉头一甜，鲜血狂喷而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "猛地向前一跃,跳出了$P"
                       CYN "的攻击范围。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
