// baiwei.c 
// gladiator

#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg; 
        object weapon;
        int extra;
        int count, i;

        extra = me->query_skill("huilong-zhang",1) + me->query_skill("staff", 1);    
        
        if (userp(me) 
        && me->query_skill("huilong-zhang", 1) <120
         && !query("can_perform/huilong-zhang/baiwei", me) )
                return notify_fail("你还不会使用「神龙摆尾」。\n");            
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「神龙摆尾」只能在战斗中对对手使用。\n");

        if( !objectp(query_temp("weapon", me) || query("skill_type", weapon) != "staff") )
                return notify_fail("使用「神龙摆尾」时双手应该持杖！\n");

        if( (int)me->query_skill("huilong-zhang", 1) < 80 )
                return notify_fail("你的回龙杖不够娴熟，不会使用「神龙摆尾」。\n");

        if( (int)me->query_skill("shaolin-xinfa", 1) < 80 )
                return notify_fail("你的内功等级不够，不能使用「神龙摆尾」。\n");
     
        if( query("neili", me)<600 )
                return notify_fail("你现在内力太弱，不能使用「神龙摆尾」。\n");

        msg = HIY "$N长啸一声，将内力聚于手中钢杖，突然一个转身，手中钢杖点向$n！\n" NOR;

        message_vision(msg, me, target); 

        count = 3;
           
        for (i=0;i < count;i++)
        {
           COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        }

        addn("neili", -100*count, me);

        me->start_busy(1+random(2));

            return 1;
}
