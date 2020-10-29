// lei.c 天打雷劈

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("天打雷劈只能在战斗中对对手使用。\n");

        if (me->query_skill("never-defeated", 1) < 150)
                return notify_fail("你的不败神功还不够娴熟，不能使用天打雷劈！\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必须手持兵刃才能施展天打雷劈！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "大喝一声，手中的" + weapon->name() +
              HIC "长劈而下，看似简单，竟然封住了$n"
              HIC "所有的退路！\n" NOR;

        ap = attack_power(me, "sword");
        dp = attack_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                ap = me->query_skill("never-defeated", 1);
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                me->want_kill(target);
                if (dp >= 10000)
                {
                        damage = damage_power(me, "sword");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                        HIR "$n" HIR "只觉此招，阴柔无比，诡异莫测，"
                                        "心中一惊，却猛然间觉得一股阴风透骨而过。\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "$n" HIR "平生何曾见过这样的招数，全然无法化解，"
                                HIR "顿时被击中数处要害，颓然倒地！\n" NOR;
                        message_combatd(msg, me, target);
                        target->die(me);
                        return 1;
                }
        } else
        {
                msg += HIM "$n" HIM "大吃一惊，连忙胡乱抵挡，居"
                                "然没有一点伤害，侥幸得脱！\n" NOR;

                me->start_busy(1 + random(3));
        }

        message_combatd(msg, me, target);

        return 1;
}