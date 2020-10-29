// huxiao.c 虎啸山林
// gladiator

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;     
        int j, k;
        int i, count;
       
        j = me->query_skill("huzhua-claw", 1);
        k = me->query_skill("claw",1);

        if( userp(me) && !query("can_perform/huzhua-claw/huxiao", me) )
                return notify_fail("你还不会使用「虎啸山林」。\n");            
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「虎啸山林」只能在战斗中对对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("使用「虎啸山林」时双手必须空着！\n");

        if( (int)me->query_skill("huzhua-claw", 1) < 120 )
                return notify_fail("你的虎爪擒拿手不够娴熟，不会使用「虎啸山林」。\n");

        if( (int)me->query_skill("shaolin-xinfa", 1) < 120 )
                return notify_fail("你的内功等级不够，不能使用「虎啸山林」。\n");

        if( (int)me->query_dex() < 27 )
                return notify_fail("你的身法不够强，不能使用「虎啸山林」。\n");

        if (me->query_skill_prepared("claw") != "huzhua-claw"
        || me->query_skill_mapped("claw") != "huzhua-claw")
                return notify_fail("你现在无法使用「虎啸山林」进行攻击。\n");                                                                                 
      

        if( query("neili", me)<600 )
                return notify_fail("你现在内力太弱，不能使用「虎啸山林」。\n");

        msg = HIR "$N长啸一声，将内力聚于手心，如猛虎下山一般扑向$n！\n" NOR;


        if( random(10) >= 5 
        && !me->is_busy() 
        && j > 120
        && k > 120
        && j > random(target->query_skill("dodge",1)))
        {
          switch(random(3))
          {
            case 0 :
               msg  = HIB "$N目露凶光，使出「黑虎掏心」，招招抓向$n胸口！\n" NOR;
               msg += HIB "$n被$N逼的连连後退，无力还招！\n" NOR;
               me->start_busy(3);
               message_combatd(msg, me, target);
               break;

            case 1 :
               msg  = MAG "$N施出「虎踞龙盘」，双手纷飞，幻出无数手影！\n" NOR;
               msg += MAG "$n只觉眼花缭乱，不知所措。\n" NOR;
               me->start_busy(1+random(2));
               message_combatd(msg, me, target);
               break;

            case 2 :
               msg  = BLU "$N一招「虎虎生威」，拿向$n，似乎$n的全身都被手影笼罩！\n" NOR;
               msg += BLU "$n只觉得周围全被手影笼罩，毫无躲闪的余地。\n" NOR;
               me->start_busy(random(3));
               message_combatd(msg, me, target);
               break;
          }
          count = 1;
          count += random(5);
          
          for (i=0;i < count;i++)
          {
           COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
          }
          addn("neili", -100*count, me);
       } else
       {
           msg += HIR "$n识破你的招式，早早提防闪到了一边。\n" NOR;
           me->start_busy(1 + random(2));
           addn("neili", -200, me);
        message_vision(msg, me, target);
       }  
       return 1;
}
