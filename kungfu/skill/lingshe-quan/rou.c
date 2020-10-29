// This program is a part of NITAN MudLIB
// rou.c 柔字诀

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "柔字诀" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「柔字诀」只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你要施展拳法不能使用武器。\n");

        if ((int)me->query_skill("lingshe-quan", 1) < 120)
                return notify_fail("你的灵蛇拳法不够娴熟，现在还无法使用「柔字诀」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，无法运用「柔字诀」。\n");

        msg = HIG "$N" HIG "一拳打出，半途中手臂忽然不可思议的转了个圈子，打向$n"
              HIG "，令$p" HIG "防不胜防。\n"NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                if (!target->is_busy())
                        target->start_busy(1);
                damage = damage_power(me, "cuff");

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只见$n" HIR "大吃一惊，仓皇之下不及闪躲，被$N"
                                           HIR "一拳打了个正中，闷哼一声，连退数步！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "见机的快，连忙施展身法，避开了拳。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}