// This program is a part of NITAN MudLIB
// fuxue.c 拈花指 「拈花拂穴」

#include <ansi.h>

inherit F_SSERVER;

string name() { return "拈花拂穴"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("拈花拂穴只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你内功火候不够，不能使用拈花拂穴！\n");

        if ((int)me->query_skill("finger") < 150)
                return notify_fail("你的指法修为不够，目前还不能使用拈花拂穴绝技！\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，不能使用拈花拂穴！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if (me->query_skill_mapped("finger") != "nianhua-zhi")
                return notify_fail("你没有激发拈花指，无法使用拈花拂穴！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "使出拈花指绝技「拈花拂穴」，罩住了$n"
              HIY "的全身，指气层层叠叠的攻向$p" HIY "的要穴！\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg +=  HIG "结果$p" HIG "被$P" HIG "攻了个措手不及！\n" NOR;
                if (! target->is_busy())
                        target->start_busy(ap/90 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        }
        else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的招式，连忙跃开，避开了$P"
                       CYN "的攻击。\n" NOR;
                addn("neili", -30, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
