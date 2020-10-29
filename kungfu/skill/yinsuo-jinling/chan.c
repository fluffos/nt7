// This program is a part of NITAN MudLIB
// chan.c 缠字诀

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "缠字诀" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("yinsuo-jinling", 1) < 80)
                return notify_fail("你银锁金铃的修为不够，不能使用缠字诀！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        msg = CYN "$N" CYN "使出银锁金铃「缠」字诀，拂鞭连挥企图把$n"
              CYN "的全身缠住。\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += CYN "结果$p" CYN "被$P" CYN "攻了个措手不及。\n" NOR;
                target->start_busy( ap / 90 + 2 );
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企图，并没有上当。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        addn("neili", -100, me);
        return 1;
}