// ying.c 霹雳刀法「刀影重重」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, zhao;

        if (! target) target = offensive_target(me);


        if (! target || ! me->is_fighting(target))
                 return notify_fail("「刀影重重」只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                 return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("pili-daofa", 1) < 120)
                 return notify_fail("你的霹雳刀法火候不够，无法施展「刀影重重」。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的真气不够，不能使用「刀影重重」。\n");

        msg = HIC "$N" HIC "身法忽变，手中" + weapon->name() + "划出片片刀影，向$n" + HIC
              "一层层卷去。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        if ( ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "只听$p" HIR "一声惨叫，"
                      "身上顿时被砍得血肉模糊，鲜血崩流！\n" NOR;
                zhao = 5;
                count = ap / 10;
        } else
        {
                msg += CYN "可是$p" CYN "奋力格挡，将$P" CYN
                       "的攻击化解。\n" NOR;
                zhao = 0;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        for (i = 0; i < zhao; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
