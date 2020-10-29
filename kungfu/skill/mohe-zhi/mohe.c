//gladiator

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev, lev2;
        string msg;
        
        lev = (int)me->query_skill("mohe-zhi", 1)/4;
        lev2 = (int)me->query_skill("finger", 1)/4;
    
        if( userp(me) && !query("can_perform/mohe-zhi/mohe", me) )
                return notify_fail("你所使用的外功中没有这样的功能。\n");
                    
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「摩诃参禅」只能在战斗中使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你拿着武器怎么能使用「摩诃参禅」！\n");   

        if( (int)me->query_skill("mohe-zhi", 1) < 80 )
                return notify_fail("你的摩诃指还不够娴熟，使不出「摩诃参禅」绝技。\n");

        if((int)me->query_skill("force") < 80 ) 
                return notify_fail("你的内功修为还不够，使不出「摩诃参禅」绝技。\n");

        if ( me->query_skill_mapped("finger") != "mohe-zhi" )
                return notify_fail("你现在无法使用「摩诃参禅」！\n"); 

        if( query("max_neili", me)<(me->query_skill("force")+1000) )
                return notify_fail("你现在内力太弱，使不出「摩诃参禅」。\n");      

        if( query("neili", me)<800 )
                return notify_fail("你现在真气太弱，使不出「摩诃参禅」。\n");

        msg = HIY "\n$N不动声色，衣袖轻摆，几缕指风无声无息弹出。\n" NOR;
        message_vision(msg, me, target); 
        
        addn_temp("apply/finger", lev, me);
        addn_temp("apply/attack", lev2, me);
        
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);

        if( random(query("combat_exp", me))>query("combat_exp", target)/2 )
        {    
               COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
               
        } else
        {
               COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        }
        addn_temp("apply/finger", -lev, me);
        addn_temp("apply/attack", -lev2, me);
        addn("neili", -350, me);
        addn("jingli", -50, me);
        me->start_busy(1 + random(2));
        target->start_busy(1);
        return 1;
}
