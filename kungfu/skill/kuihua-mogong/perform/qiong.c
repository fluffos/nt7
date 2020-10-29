// qiong 无穷无尽

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define QIONG "「" HIR "无穷无尽" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, ap1, dp1, damage;
        mixed dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIONG "只能在战斗中对对手使用。\n");

        if (me->query_skill("kuihua-mogong", 1) < 250)
                return notify_fail("你的葵花魔功还不够娴熟，不能使用" QIONG "！\n");

        if( query("max_neili", me)<3800 )
                return notify_fail("你的内力修为不足，难以施展" QIONG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法施展" QIONG "\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("你手里拿的不是剑，怎么施"
                                           "展" QIONG "？\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "kuihua-mogong")
                        return notify_fail("你并没有准备使用葵"
                                           "花魔功，如何施展" QIONG "？\n");
        }
        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("你没有准备使用葵花魔功，难以施展" QIONG "。\n");

        if (! weapon && me->query_skill_prepared("finger") != "kuihua-mogong")
                return notify_fail("你没有准备使用葵花魔功，难以施展" QIONG "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "\n$N" HIR "尖啸一声，猛然进步欺前，一招竟直袭$n" HIR "要害，速度之快，令"
              "人见所未见，闻所未闻。\n" NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->want_kill(target);
                ap = me->query_skill("kuihua-mogong", 1);
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                if (dp >= 10000) // 对百万经验以上无效，但是仍然受到伤害
                {
                        if (weapon) damage = damage_power(me, "sword");
                        else damage = damage_power(me, "unarmed");
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 95 + random(5),
                                                HIR "这一招速度之快完全超出了$n" HIR "的想象，$n" HIR
                                                "慌忙回缩招架，但是此招之快，已无从躲闪，$n" HIR "尖叫"
                                                "一声，已然中招。\n" NOR);

                        message_sort(msg, me, target);
                        return 1;
                } else
                // if (random(ap) > dp)
                {
                        msg += HIR "这一招速度之快完全超出了$n" HIR "的想象，被$N"
                               HIR "这一招正好击中了丹田要害，浑身真气登时涣散！\n" NOR;
                        message_combatd(msg, me, target);
                        addn("neili", -120, me);
                        target->receive_damage("qi", 1, me);
                        target->die(me);
                        return 1;
                }

        } else
                msg += HIM "$n" HIM "大吃一惊，连忙退后，居然"
                                "侥幸躲开着这一招！\n" NOR;

        me->start_busy(1 + random(2));
        message_combatd(msg, me, target);

        return 1;
}