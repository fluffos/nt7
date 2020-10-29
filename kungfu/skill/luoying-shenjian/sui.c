#include <ansi.h>
#include <combat.h>

string name() { return HIG "随波逐流" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((int)me->query_skill("luoying-shenjian", 1) < 80)
                return notify_fail("你落英神剑不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "luoying-shenjian")
                return notify_fail("你没有激发落英神剑，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不足，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "手中" + weapon->name() + HIG "疾转，剑幕缭绕，引得周"
              "围气流波动不已，笼罩$n" HIG "四方。\n" NOR;

        addn("neili", -80, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$n" HIR "勘不透$N" HIR "招中奥妙，不敢擅自出招，顿时"
                       "便失了先机。\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "不慌不忙，看破了此招"
                       "虚实，并没有受到半点影响。\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}