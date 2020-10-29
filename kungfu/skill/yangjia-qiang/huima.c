//  huima.c 回马枪 
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return WHT"回马枪"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i;
    i = me->query_skill("yangjia-qiang", 1) /3;
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「回马枪」只能对战斗中的对手使用。\n");

    if((int)me->query_skill("force", 1) < 250 )
                return notify_fail("你的基本内功不够娴熟，无法支持「回马枪」。\n");

    if( (int)me->query_skill("yangjia-qiang", 1) < 250 ) 
                return notify_fail("你的枪法还未练成，不能使用「回马枪」！\n");

    if((int)me->query_skill("spear", 1) < 250 )
                return notify_fail("你的基本枪法不够娴熟，不能在剑招中使用「回马枪」。\n");

    if((int)me->query_skill("dodge", 1) < 250 )
                return notify_fail("你的基本轻功不够娴熟，不能使用「回马枪」。\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "spear"
        || me->query_skill_mapped("spear") != "yangjia-qiang"
        || me->query_skill_mapped("parry") != "yangjia-qiang")
                return notify_fail("你手里无枪，如何使用「回马枪」？\n");
                
    if((int)me->query("max_neili") < 8000 )
                return notify_fail("你的内力修为不够，不能使用「回马枪」！\n");

    if((int)me->query("neili") < 3000 )
                return notify_fail("你现在真气不足，不能使用「回马枪」！\n");

    if((int)me->query("jingli") < 1000 )
                return notify_fail("你现在太累了，不能使用「回马枪」！\n");
      
message_vision(HIB"\n$N忽然纵身跃起，竟使出杨家枪之"YEL"「回马枪」"HIB"绝技，只见枪锋到处迸发出一阵漩涡，让四周之人胆颤心惊！\n"NOR, me,target);

    me->start_perform(3,"「回马枪」");
    me->add("neili", -800);
    me->add("jingli",-500);
    me->set_temp("yjq/huima",1);

    me->add_temp("apply/attack", i);
    me->add_temp("apply/damage",i);
    
	target->set_temp("must_be_hit",1);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
   target->delete_temp("must_be_hit");
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
   
   me->add_temp("apply/damage", -i);
   me->add_temp("apply/attack", -i);
    me->delete_temp("yjq/huima");
    me->start_busy(1);
    target->start_busy(1);
    return 1;
}

int help(object me)
{
   write(YEL"\n杨家枪「"HIG"回马枪"YEL"」："NOR"\n");
   write(@HELP
   指令：perform huima

   要求：杨家枪250级，
         基本枪法250级，
         最大内力 8000 以上，
         当前内力 3000 以上，
         当前精力 1000 以上，
         激发杨家枪为招架。
HELP
   );
   return 1;
}