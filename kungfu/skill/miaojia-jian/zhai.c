#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { HIW "云边摘月" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((level = me->query_skill("miaojia-jian", 1)) < 100)
                return notify_fail("你苗家剑法不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("你没有激发苗家剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "一声清哮，剑势舒张，吞吐不定，瞬间向$n" HIW "连刺"
              "数剑，企图扰乱$n" HIW "的攻势。\n" NOR;

        addn("neili", -30, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果$p" HIR "只见$P" HIR "剑招精妙，全然"
                       "辨不清招中虚实，攻势登时一紧！\n" NOR;
                target->start_busy(level / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "剑势的来路，"
                       "径自出招，丝毫不为所动。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}