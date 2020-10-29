// This program is a part of NITAN MudLIB
// chan.c

#include <ansi.h>

inherit F_SSERVER;
string name() { return "缠绕诀"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你没有拿着鞭子。\n");

        if( query("neili", me)<80 )
                return notify_fail("你现在真气不够，无法施展「缠绕」诀！\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("你没有激发日月鞭法，无法施展「缠绕」诀！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "使出日月鞭法「缠绕」诀，连挥数鞭企图把$n"
              HIC "的全身缠绕起来。\n";

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果$p" HIR "被$P" HIR "攻了个措手不及！\n" NOR;
                target->start_busy(ap/80 +2);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企图，小心应对，并没有上当。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
