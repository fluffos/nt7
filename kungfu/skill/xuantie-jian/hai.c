// This program is a part of NITAN MudLIB
// 海潮汹涌

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "海潮汹涌"; }

string *xue_name = ({
        "劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
        "幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
});

int perform(object me, object target)
{
        string msg, dodge_skill;
        int i, j, ap, dp;
        object weapon;

        if( query("gender", me) == "男性" )
        {
                i = me->query_skill("xuantie-jian", 1) / 4;
                j = me->query_skill("sword", 1) / 4;
        }
        else
        {
                i = me->query_skill("xuantie-jian", 1) / 5;
                j = me->query_skill("sword", 1) / 5;
        }
        weapon=query_temp("weapon", me);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("玄铁剑法的「海潮汹涌」只能在战斗中对对手使用。\n");

        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你必须使用武器才能使用「海潮汹涌」！\n");

        if ((int)me->query_skill("xuantie-jian", 1) < 130)
                return notify_fail("你的玄铁剑法还不够娴熟，使不出「海潮汹涌」绝技。\n");

        if ((int)me->query_skill("surge-force", 1) < 130
        &&  (int)me->query_skill("surge-force", 1) < 130)
                return notify_fail("你的古墓内功等级还不够，使不出「海潮汹涌」绝技。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的内功等级不够，不能使用「海潮汹涌」。\n");

        if ((int)me->query_str() < 33)
                return notify_fail("你的膂力还不够强劲，使不出「海潮汹涌」来。\n");

        if( query_temp("xtjf/haichao", target) || target->is_busy() )
                return notify_fail(target->name()+"正自顾不暇，你可以放心地进攻。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian" && userp(me))
                return notify_fail("你现在无法使用「海潮汹涌」！\n");

        if (me->query_skill_mapped("parry") != "xuantie-jian" && userp(me))
                return notify_fail("你现在无法使用「海潮汹涌」！\n");

        if( query("max_neili", me)<(me->query_skill("force")+j+200) )
                return notify_fail("你现在内力太弱，使不出「海潮汹涌」。\n");

        message_combatd(HIB"\n$N持"+query("name", weapon)+
                        HIB "挟巨浪潮涌之势，剑气形成一个旋转的气涡，向$n笼罩过去。\n" NOR,
                        me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        
        if (query("can_perform/surge-force/new", me) && me->query_skill("surge-force", 1) )
	{
		ap += ap / 2;
	}
	
        if (ap / 2 + random(ap) > dp)
        {
                message_combatd(HIR "结果$n全身被剑气所形成的气涡所笼罩着，只觉得犹如身陷洪涛巨浪，跌跌撞撞。\n" NOR,
                                me, target);

                if( !target->is_busy() )
                        target->start_busy(2 + ap / 80);
                set_temp("xtjf/haichao", 1, target);
                addn("neili", -i*3, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);

                if (me->query_skill("xuantie-jian", 1) > 180)
                {
                        remove_call_out("remove_effect");
                        call_out("remove_effect", 1, me, target);
                }

                if ((int)me->query_skill("xuantie-jian", 1) > 150
                 && query("neili", me)>(me->query_skill("force",1)+j )
                &&  present(target, environment(me))
                &&  me->is_fighting(target))
                {
                        message_combatd(HIB"\n$N微笑不语，趁势将手中的"+query("name", weapon)+
                                        HIB "从轻而响，从响而轻，忽寂然无声，忽轰轰之声，向$n席卷而去。\n" NOR,
                                        me, target);

                        if (random(me->query_skill("sword", 1)) > target->query_skill("parry", 1) / 3
                        ||  ! living(target)
                         || query("level", me)>query("level", target) )
                        {
                                addn_temp("apply/str", i, me);
                                addn_temp("apply/attack", j, me);
                                addn_temp("apply/damage", j, me);
                                set_temp("xtjf_pfm", 1, me);
                                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                                addn_temp("apply/str", -i, me);
                                addn_temp("apply/attack", -j, me);
                                addn_temp("apply/damage", -j, me);

                                addn("neili", -200, me);
                                delete_temp("xtjf_pfm", me);
                        } else
                        {
                                addn("neili", -100, me);
                                dodge_skill = target->query_skill_mapped("dodge");
                                if (! dodge_skill ) dodge_skill = "dodge";
                                        msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                                message_combatd(msg, me, target);
                        }
                        return 1;
                }
        } else
        {
                me->start_busy(2+random(2));
                addn("neili", -100, me);
                dodge_skill = target->query_skill_mapped("dodge");
                if (! dodge_skill ) dodge_skill = "dodge";
                        msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                message_combatd(msg, me, target);
        }
        return 1;
}

void remove_effect(object me, object target)
{
        remove_call_out("remove_effect");
        if (! me) return;
        if (objectp(target) && ! me->is_fighting(target))
        {
                delete_temp("xtjf", target);
                return;
        }
        if (objectp(target)
        &&  me->is_fighting(target)
        &&  ! target->is_busy()
        &&  random(2) == 1
         && query_temp("weapon", me) )
        {
                delete_temp("xtjf", target);
                call_out("perform2", 0, me, target);
                return;
        }
        call_out("remove_effect", 1 ,me ,target);
}

int perform2(object me, object target)
{
        string msg, dodge_skill,name;
        object weapon=query_temp("weapon", me);
        int p, ap, dp, damage;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return 0;

        if( !weapon || query("skill_type", weapon) != "sword" )
                return 0;
        if( me->query_skill_mapped("sword") != "xuantie-jian" && userp(me))
                return 0;

        if( me->query_skill_mapped("parry") != "xuantie-jian" && userp(me))
                return 0;

        if( query("neili", me)<1000 )
                return 0;

        if( query("gender", me) == "女性" )
                p = me->query_skill("force", 1) / 6;
        else
                p = me->query_skill("force", 1) / 8;

        name = xue_name[random(sizeof(xue_name))];
        msg =HIB"\n$n好不容易缓过劲来，$N身形飘忽，转了几转，移步向西，紧跟一剑刺向$n的"RED+name+HIB"。\n"NOR;

        ap=attack_power(me, "sword");
        dp=defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += CYN"$n顿觉眼前一阵迷惑，一时不备，身上的"RED+name+CYN"已被"+weapon->name()+CYN"点中。\n"NOR;
                addn_temp("apply/attack", -p/2, target);
                addn_temp("apply/defense", -p/2, target);
                target->set_temp("xtjf/haichao");
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", random(damage/2)+damage/2, me);
                if( random(2) == 1)
                {
                        target->apply_condition("no_perform", 1+ random(2));
                        target->set_temp("xtjf/perform");
                }
                else
                {
                        target->apply_condition("no_exert", 1+random(2));
                        target->set_temp("xtjf/exert");
                }
                addn("neili", -p*6, me);
                call_out("check_fight", 1, me, target, weapon, p );
        }
        else {
                me->start_busy(2+random(2));
                addn("neili", -100, me);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                        msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_combatd(msg, me, target);
        return 1;
}

void check_fight(object me,object target,object weapon, int p)
{
        remove_call_out("check_fight");
        if( !target) return;
        if( ! me
         || ! me->is_fighting("target")
          || !query_temp("weapon", me )
          || query("skill_type", weapon) != "sword"
         || ! present(target,environment(me))
         || me->query_skill_mapped("sword") != "xuantie-jian"){
                addn_temp("apply/attack", p/2, target);
                addn_temp("apply/defense", p/2, target);
                if( query_temp("xtjf/perform", target) )
                        target->clear_condition("no_perform");
                if( query_temp("xtjf/exert", target) )
                        target->clear_condition("no_exert");
                delete_temp("xtjf", target);
                message_combatd(HIW"\n$N竭力挣脱了纠缠，身形恢复了原先的矫捷。\n"NOR, target);
                return ;
        }
        call_out("check_fight", 1, me, target, weapon, p );
}
