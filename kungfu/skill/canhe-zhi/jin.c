// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "金刚剑气" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用" + name() + "。\n");

        if ((int)me->query_skill("canhe-zhi", 1) < 160)
                return notify_fail("你的参合指修为有限，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("你现在没有准备使用参合指，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "双手合十，微微一笑，颇得拈花之意。食指并中指"
              "轻轻一弹，顿时一屡罡气电射而出，朝$n" HIY "袭去。\n" NOR;

        ap=attack_power(me, "finger") + me->query_skill("force", 1);
        dp=defense_power(target, "force") + target->query_skill("buddhism",1);
        me->start_busy(2);

        if ((int)target->query_skill("buddhism", 1) >= 200
            && random(5) == 1)
        {
                addn("neili", -400, me);
                me->start_busy(3);
                msg += HIY "但见$n" HIY "也即脸露笑容，衣袖轻轻一拂，顺势"
                       "裹上，顿将$N" HIY "的指力消逝殆尽。\n" NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75,
                                           (: final, me, target, damage :));
        } else
        {
                addn("neili", -200, me);
                me->start_busy(4);
                msg += CYN "$n" CYN "见$N" CYN "来势汹涌，不敢轻易"
                       "招架，急忙提气跃开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 6, me);
        target->receive_wound("jing", damage / 10, me);
        return  HIR "只听“噗嗤”一声，指力竟在$n" HIR
                "胸前穿了一个血肉模糊的大洞，透体而入。\n" NOR;
}
