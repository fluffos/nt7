// jiang.c 神龙天降

#include <ansi.h>

inherit F_SSERVER;
string name() { return "神龙天降"; }

int perform(object me, object target)
{
        object weapon;
        string msg,force;
        int damage,sk1,sk2,exp1,exp2,skill,dp,ap;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「神龙天降」只能在战斗中使用。\n");


        skill = (int)me->query_skill("shenlong-jian",1);

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( skill < 300 )
                return notify_fail("你的神龙剑法不够娴熟，不会使用「神龙天降」。\n");

        if( (int)me->query_skill("busi-shenlong", 1) <100
                 && (int)me->query_skill("shenlong-xinfa", 1)<100)
                return notify_fail("你的内功火候不够，无法发挥剑法威力。\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在内力太弱，不能使用绝招。\n");

        if ( me->query_skill_mapped("force") != "busi-shenlong"
                 && me->query_skill_mapped("force") != "shenlong-xinfa")
                 return notify_fail("你没有运用神龙教系列内功！\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        msg = CYN "$N后跃一步，手捏剑决，口中念念有词，突然大喝一声「神龙天降」！！\n"NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if( !target->is_busy() )
                {
                        if(skill<350)
                                target->start_busy(1 + random(2));
                        else
                                target->start_busy(1 + random(3));
                }
                damage = damage_power(me, "sword");

                target->receive_damage("qi", damage/2,me);
                target->receive_damage("jing", damage/3,me);
                target->receive_wound("jing", damage,me);
                addn("neili", -damage, me);
                msg += HIY"$N的剑法顿时变得诡异十分，幻出朵朵剑花，犹如数条金龙，迅速向$n飞去！\n"
                       "$n试图避开剑招，可全身僵硬不能动弹，疑惑中已经身中数剑，精神愈加恍惚起来！\n"NOR;
                me->start_busy(3);
        }
        else
        {
                msg += CYN"$n顿感身体被制，情知不妙，立刻摄守神元，终于突破对方控制。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}

