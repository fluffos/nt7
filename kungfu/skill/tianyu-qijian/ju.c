// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "聚剑诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("tianyu-qijian", 1) < 130)
                return notify_fail("你的天羽奇剑不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill("force", 1) < 180)
                return notify_fail("你的内功火候不足，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        msg = HIR "$N" HIR "手腕轻轻一抖，手中的" + weapon->name() +
              HIR "化作一道彩虹，光华眩目，笼罩了$n" HIR "。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "只见$N" HIR "剑花聚为一线，穿向$n"
                                           HIR "，$p" HIR "只觉一股热流穿心而过，"
                                           "喉头一甜，鲜血狂喷而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "猛地向前一跃,跳出了$P"
                       CYN "的攻击范围。\n"NOR;
                addn("neili", -80, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
