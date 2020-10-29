// shou.c 九阴神手

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#define SHOU  "「" HIG "九阴神手" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, ap1, dp1, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHOU "只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("此招只能空手施展！\n");

        if (me->query_skill("jiuyin-shengong", 1) < 260)
                return notify_fail("你的九阴神功还不够娴熟，不能使用" SHOU "！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够！\n");

        if (me->query_skill_mapped("hand") != "jiuyin-shengong"
           && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("你没有准备使用九阴神功，无法施展" SHOU "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "“哈”的一声吐出了一口气，手式奇特，软绵绵的奔向$n"
              HIY "的要穴！\n";

        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                ap = me->query_skill("jiuyin-shengong");
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(3));

                me->want_kill(target);

                if (dp >= 10000) // 此招对千万经验以上的人无效
                { // 但是仍然受到伤害
                        damage = damage_power(me, "hand");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                        HIR "$n" HIR "只觉此招，阴柔无比，诡异莫测，"
                                        "心中一惊，却猛然间觉得一股阴风透骨而过。\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "这一招完全超出了$n" HIR "的想象，被$N"
                                HIR "结结实实的打中了檀中大穴，浑身真气登时涣散！\n" NOR;
                        message_combatd(msg, me, target);
                        addn("neili", -200, me);
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