// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "五阴焚灭" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 240)
                return notify_fail("你的先天功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你没有激发先天功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你没有激发先天功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("你没有准备使用先天功，难以施展" + name() + "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "体内先天真气急速运转，单掌一抖，掌心顿时升起一个气"
              "团，朝$n" HIW "猛拍而去。\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        msg += HIR "$n" HIR "正直诧异间，$N" HIR "一掌已正中$p"
                               HIR "脑门，先天真气登时贯脑而入。\n" NOR "( $n"
                               RED "受伤过重，已经有如风中残烛，随时都可能断气"
                               "。" NOR ")\n";
                        damage = -1;
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        addn("neili", -500, me);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
                                                   HIR "结果$N" HIR "这掌正中$n" HIR "胸"
                                                   "口，先天真气登时透体而入，接连喷出数"
                                                   "口鲜血。\n" NOR);
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -120, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃躲避开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->unconcious(me);

        return 1;
}