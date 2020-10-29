// cui.c 催魂

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "催魂"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「催魂」只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你只能空手使用「催魂」绝技。\n");

        ap = attack_power(me, "hand");

        if (ap < 150)
                return notify_fail("你的天魔手等级不够, 无法使用「催魂」！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真气不够，无法运用「催魂」！\n");

        msg = HIR "$N" HIR "步法忽变，左右横跨数步，口中吟吟有声，双手向$n" HIR
              "缓缓拍到。\n" NOR;

        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -120, me);
                damage = damage_power(me, "hand");
                target->receive_damage("jing", damage/3, me);
                target->receive_wound("jing", damage/5, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "正自惊疑，不及闪避，登时被"
                                           "拍个正着。顿感精神不济，摇摇欲倒！\n" NOR);
                me->start_busy(1 + random(3));
        } else
        {
                addn("neili", -50, me);
                msg += CYN "$n" CYN "见来势奇异，精神一振，奋力化解了$N"
                       CYN "这一招。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
