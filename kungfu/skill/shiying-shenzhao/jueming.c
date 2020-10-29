// jueming.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "绝命"; }

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
                return notify_fail("「绝命」只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你只能空手使用「绝命」。\n");

        ap = attack_power(me, "claw");

        if (ap < 150)
                return notify_fail("你的弑鹰神爪等级不够, 无法使用「绝命」！\n");

        if( query("neili", me)<180 )
                return notify_fail("你的真气不够，无法运用「绝命」！\n");

        msg = HIR "$N" HIR "一声暴喝，手臂上青筋突起，左手一晃，右手成爪，向$n" HIR
              "前胸迅疾抓到。\n" NOR;

        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "闪避不及，前胸顿时被抓出"
                                           "五条血痕，不禁长声惨呼！\n" NOR);
                me->start_busy(2 + random(2));
        } else
        {
                addn("neili", -50, me);
                damage = damage_power(me, "claw") / 5;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIM "$n" HIM "不敢小觑此招，拼力拆解，"
                                           "但双臂仍被抓出了几条血印！\n" NOR);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
