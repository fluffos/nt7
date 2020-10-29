// 铁掌掌法 -- 阴阳合一
// Modified by snowman@SJ 19/12/2000

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string perform_name(){ return HBBLU"阴阳合一"NOR; }
int perform(object me, object target)
{
        int j;

        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !living(target)
          || environment(target)!= environment(me))
                return notify_fail("「阴阳合一」只能在战斗中对对手使用。\n");

        if( me->query_temp("weapon") )
                return notify_fail("你必须空手才能使用「阴阳合一」！\n");

        if( (int)me->query_skill("super-strike", 1) < 200 )
                return notify_fail("你的铁掌掌法还不够娴熟，使不出「阴阳合一」绝技。\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的归元吐纳法等级不够，使不出「阴阳合一」绝技。\n");

        if( (int)me->query_skill("force") < 230 )
                return notify_fail("你的内功等级不够，不能使用「阴阳合一」。\n");

        if( (int)me->query_str() < 33 )
                return notify_fail("你的膂力还不够强劲，使不出「阴阳合一」来。\n");

        if (me->query_skill_prepared("strike") != "super-strike"
         || me->query_skill_mapped("strike") != "super-strike"
         || me->query_skill_mapped("parry") != "super-strike")
                return notify_fail("你现在无法使用「阴阳合一」！\n");    
        
        if( (int)me->query("max_neili") < 1500)
                return notify_fail("你现在内力太弱，使不出「阴阳合一」。\n");      

        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出「阴阳合一」。\n");

        if((int)me->query_temp("tzzf") && userp(me)) 
                return notify_fail("你正在使用掌刀。\n");

	j = me->query_skill("super-strike", 1)/3;
        message_vision(HIW"\n$N退了两步，突然身子微侧，紧跟着身形猛进直击$n！\n"NOR, me, target);

        me->add_temp("apply/strike", j);
        me->add_temp("apply/damage", j/2);
        me->add_temp("apply/attack", j);
        me->set_temp("tz/heyi", 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->set_temp("tz/heyi", 2);
        if(me->is_fighting(target)){
          	if(random(me->query("combat_exp",1)) > target->query("combat_exp", 1)/3)
            		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          	else
            		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        }
        me->delete_temp("tz/heyi");
        me->add_temp("apply/strike", -j);
        me->add_temp("apply/damage", -j/2);
        me->add_temp("apply/attack", -j);
        if( j * 4 > 250 && random(2) ){
        	tell_object(me, HIY"\n紧接着你掌势一变，开始凝聚秘传的“天雷气”……\n"NOR);
        	me->start_call_out( (: call_other, __DIR__"tianlei", "tianlei_hit", me, 2 :), 1 );
        }
        me->add("neili", -500);
        me->add("jingli", -100);
        me->start_perform(5,"「阴阳合一」");
        return 1;
}

int help(object me)
{
        write(WHT"\n铁掌掌法「阴阳合一」："NOR"\n");
        write(@HELP
        这是裘千仞铁掌功的十三绝招之一，叫作「阴阳合一」，最是猛恶无比。
        而且据帮中护法说，还看过帮主在此招之后出过一式杀招！
        
        要求：  内力 1000 以上；      
                最大内力 1500 以上；
                精力 100 以上；  
                后天膂力 33 以上；
                铁掌掌法等级 140 以上；
                归元吐纳法等级 140 以上；    
                且手无兵器。
HELP
        );
        return 1;
}
