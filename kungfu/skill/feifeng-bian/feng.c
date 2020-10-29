// This program is a part of NT MudLIB
// feng.c 凤朝凰

#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

string name() { return "凤朝凰"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int count;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail( "凤朝凰只能在战斗中使用\n");


        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不对。\n");


        if (me->query_skill("force") < 150)
                return notify_fail("你的内功的修为不够，不能使用「凤朝凰」！\n");

        if (me->query_skill("feifeng-bian", 1) < 150)
                return notify_fail("你的飞凤鞭法修为不够，目前不能使用「凤朝凰」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，无法使用「凤朝凰」！\n");

        if (me->query_skill_mapped("whip") != "feifeng-bian")
                return notify_fail("你没激发飞凤鞭法，不能使用「凤朝凰」！\n");

        msg = HIY "$N" HIY "冲着" HIY "$n" HIY "轻佻一笑，向前急冲,手中" + weapon->name() +
              HIY "却毫不停留，一招「凤朝凰」\n"
              HIY "如凰洗空，长凤戏羽，"
              HIY "乱雨倾盆般分点" HIY "$n" HIY "左右!! \n" NOR;

        ap = attack_power(me, "whip");
        if (living(target))
                 dp = defense_power(target, "parry");
        else     dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果$p" HIR "被$P" HIR
                       "攻了个措手不及，目接不暇，疲于奔命！\n" NOR;
                count = ap/10;

                addn_temp("apply/attack", count, me);

        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "鞭势狠辣，心下凛然，凝神应付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        addn("neili", -150, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(4));
        return 1;
}