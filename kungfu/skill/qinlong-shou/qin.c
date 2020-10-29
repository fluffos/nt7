//edit by gladiator 擒龙打

#include <ansi.h>
#include <combat.h>

#define QIN "「" HIR "擒龙打" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string wn, msg;

        if (! target) target = offensive_target(me);

        if( userp(me) && me->query_skill("qinlong-shou",1)<120 && !query("can_perform/qinlong-shou/qin", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIN "只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你使用的武器不对，难以施展" QIN "。\n");

        if (me->query_skill("force") < 100)
                return notify_fail("你的内功的修为不够，难以施展" QIN "。\n");

        if (me->query_skill("qinlong-shou", 1) < 100)
                return notify_fail("你的擒龙手修为不够，难以施展" QIN "。\n");

        if (me->query_skill_mapped("hand") != "qinlong-shou")
                return notify_fail("你没有激发擒龙手，难以施展" QIN "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你现在真气不够，难以施展" QIN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIC "$N" HIC "施出「" HIR QIN HIC "」绝技，" +
              HIC "微作龙吟，双手曲成爪抓向$n" HIC "。\n" NOR;

        ap = me->query_skill("hand");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap * 2 / 3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -150, me);
        } else
        {
                msg += CYN "可是$p" CYN "并不慌乱，收敛心神，轻轻格挡开了$P"
                       CYN "的剑招。\n"NOR;
                me->start_busy(3);
                addn("neili", -60, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        addn("neili", -damage, target);

        if( query("neili", target)<0 )
                set("neili", 0, target);

        return  HIR "结果$n" HIR "不慎被$N" HIR "手指射出的"
                "指气爪中劳宫穴，全身真气不禁狂泄而出！\n" NOR;
}