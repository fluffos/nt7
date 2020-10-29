#include <ansi.h>
#include <combat.h>

string name() { return HIC "兰花拂穴" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((int)me->query_skill("lanhua-shou", 1) < 120)
                return notify_fail("你兰花拂穴手不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("hand") != "lanhua-shou")
                return notify_fail("你没有激发兰花拂穴手，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("hand") != "lanhua-shou")
                return notify_fail("你没有准备兰花拂穴手，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "反手轻轻伸出三指，婉转如一朵盛开的兰花，轻点$n"
              HIC "胁下要穴。\n";

        ap = attack_power(me, "hand");

        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                msg +=  HIR "$p" HIR "只觉胁下一麻，已被$P"
                        HIR "点个正着，顿时全身酸软，呆立当场。\n" NOR;
                target->start_busy(ap / 90 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企图，轻轻一跃，跳了开去。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
