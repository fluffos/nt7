// sheng.c 无声无息

#include <ansi.h>

inherit F_SSERVER;

#define XI "「" HIW "无声无息" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XI "只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
                
        if ((int)me->query_skill("kuihua-mogong", 1) < 200)
                return notify_fail("你的葵花魔功不够深厚，不会使用" XI "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力修为不足，难以施展" XI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法施展" XI "！\n");

        if (me->query_skill_mapped("dodge") != "kuihua-mogong")
                return notify_fail("你还没有激发葵花魔功为轻功，无法施展" XI "。\n");            

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "身子忽进忽退，身形诡秘异常，在$n"
              HIR "身边飘忽不定。\n" NOR;

        ap = attack_power(me, "dodge");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果$p" HIR "只能紧守门户，不敢妄自出击！\n" NOR;
                target->start_busy(ap / 120 + 2);
                addn("neili", -120, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的身法，并没"
                       "有受到任何影响。\n" NOR;
                me->start_busy(1 + random(2));
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}