// mie.c 五阴焚灭

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("五阴焚灭只能在战斗中对对手使用。\n");

        if (me->query_skill("bluesea-force", 1) < 150)
                return notify_fail("你的南海玄功还不够娴熟，不能使用五阴焚灭！\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("你没有激发掌法为南海玄功，无法施展五阴焚灭！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "暴喝一声，变掌为爪，迅捷无比的袭向$n！\n";

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                ap = me->query_skill("bluesea-force");
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                me->want_kill(target);
                // if (dp >= 10000)
                if( query("max_neili", me)<query("max_neili", target)*2 )
                {
                        damage = damage_power(me, "strike");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                        HIR "$n" HIR "只觉此招，阴柔无比，诡异莫测，"
                                        "心中一惊，却猛然间觉得一股阴风透骨而过。\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "这一招完全超出了$n" HIR "的想象，被$N"
                                HIR "结结实实的抓中了气海穴，浑身真气登时涣散！\n" NOR;
                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
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