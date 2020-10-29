// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"夺命铁爪"NOR; }
int perform(object me, object target)
{
        int skill;
        skill = (int)me->query_skill("super-strike", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「夺命铁爪」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「夺命铁爪」！\n");   
   if(me->query_skill("force",1) < 200 )
                return notify_fail("你的归元吐呐法不够娴熟，使不出「夺命铁爪」。\n");
        if(me->query_skill_mapped("strike") != "super-strike" )
               return notify_fail("你现在无法使用「夺命铁爪」！\n");
        if( (int)me->query("max_neili") < 3000)
                return notify_fail("你现在内力太弱，使不出「夺命铁爪」。\n");      
        if( (int)me->query("neili") < 2500 )
                return notify_fail("你现在真气太弱，使不出「夺命铁爪」。\n");
      
        message_vision(HBBLU"\n$N左掌拍出，右手成抓，同时袭到，两股强力排山倒海般压向$n！\n"NOR,me,target);
        if (random(me->query_dex()) > target->query_dex()/3) {
           message_vision(HIR"结果$n被$N右手牢牢抓住！\n"NOR,me,target);
           if(!target->is_busy()) target->start_busy(2);
        }
        message_vision(HBBLU"\n$N左掌一掌掌的拍向$n！\n"NOR,me,target);
        me->add("neili", -800-random(200));
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->start_perform(6,"「夺命铁爪」");
        return 1;
}

