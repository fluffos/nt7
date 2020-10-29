// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "仙游诀" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只有在战斗中才能使用。\n");

        if ((level = me->query_skill("xiaoyaoyou", 1)) < 100)
                return notify_fail("你的逍遥游掌法不够熟练，难以施展"+name()+"。\n");

        if (me->query_skill_mapped("dodge") != "xiaoyaoyou")
                return notify_fail("你没有激发逍遥游为轻功，难以施展"+name()+"。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不足，难以施展"+name()+"。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "身子微晃，施出「" HIG "仙游诀"
              HIW "」满场游走，步法洋洋洒洒，甚为飘逸。\n" NOR;

        ap = attack_power(me, "dodge");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "只见无数人影奔来，不由大"
                       "惊失色，攻势顿为缓滞。\n" NOR;
                target->start_busy(level / 80 + 2);
                me->start_busy(1);
                addn("neili", -80, me);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$P" CYN "的身"
                       "法，并没有受到任何影响。\n" NOR;
                me->start_busy(2);
                addn("neili", -50, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
