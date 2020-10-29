 // duoming.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "夺命银龙"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail( "夺命银龙只能在战斗中使用\n");


        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不对。\n");


        if (me->query_skill("force") < 150)
                return notify_fail("你的内功的修为不够，不能使用「夺命银龙」！\n");

        if (me->query_skill("yinlong-bian", 1) < 150)
                return notify_fail("你的银龙鞭修为不够，目前不能使用「夺命银龙」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，无法使用「夺命银龙」！\n");

        if (me->query_skill_mapped("whip") != "yinlong-bian")
                return notify_fail("你没有激发银龙鞭，不能使用「夺命银龙」！\n");

        msg = HIB "突然之间，" HIB "$N" HIB "身形一闪一晃，疾退数丈,"+ weapon->name() +
              HIB "从右肩急甩向后，陡地"
              HIB "鞭头击向\n" HIB "$n" HIB "面门。" HIB "$N" HIB "本来与"
              HIB "$n" HIB "相隔十丈有余,但"+ weapon->name() +
              HIB "说到便到，正如天"
              HIB "外\n游龙，矢矫而至。！\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");
        attack_time = 5;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "结果$p" HIR "被$P" HIR
                       "攻了个措手不及，目接不暇，疲于奔命！\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                attack_time += random(ap / 90);
        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "鞭势狠辣，心下凛然，凝神应付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 10)
                attack_time = 10;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(5));
        return 1;
}