// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "缠字诀" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int level;
        int ap, dp;
        int fmsk = me->query_skill("bixue-danxin", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        level = me->query_skill("dagou-bang", 1);

        if (level < 60)
                return notify_fail("你打狗棒法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你没有激发打狗棒法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不足，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "使出打狗棒法「" HIC "缠" HIG "」字诀，棒头在"
              "地下连点，连绵不绝地挑向$n" HIG "的小腿和脚踝。\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) +fmsk > dp)
        {
                msg += HIR "棒影窜动间$n" HIR "招式陡然一紧，已被$N"
                       HIR "攻的蹦跳不停，手忙脚乱！\n" NOR;
                target->start_busy(ap/90 + 3);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企图，镇定解招，一丝不乱。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
