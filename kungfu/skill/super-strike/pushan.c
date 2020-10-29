// by darken@SJ
#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;
 string perform_name(){ return HBBLU"铁蒲扇掌"NOR; }
 int perform(object me, object target)
 {
         int j;
         string msg;
         j = me->query_skill("super-strike", 1);

         if( !target ) target = offensive_target(me);

         if( !target 
           || !me->is_fighting(target)
           || !living(target)
           || environment(target)!= environment(me))
                 return notify_fail("「铁蒲扇掌」只能在战斗中对对手使用。\n");

         if( objectp(me->query_temp("weapon")) )
                 return notify_fail("你必须空手才能使用「铁蒲扇掌」！\n");

         if( (int)me->query_skill("super-strike", 1) < 250 )
                 return notify_fail("你的铁掌不够娴熟，使不出「铁蒲扇掌」绝技。\n");

         if( (int)me->query_skill("force", 1) < 250 )
                 return notify_fail("你归元吐纳法不够，使不出「铁蒲扇掌」绝技。\n");

         if( (int)me->query("jiali") < 120 )
                 return notify_fail("你加力不够，使不出「铁蒲扇掌」绝技。\n");

         if( (int)me->query_skill("force") < 250 )
                 return notify_fail("你的内功等级不够，不能使用「铁蒲扇掌」。\n");

         if( (int)me->query_str() < 40 )
                 return notify_fail("你的膂力还不够强劲，使不出「铁蒲扇掌」来。\n");

         if (me->query_skill_prepared("strike") != "super-strike"
          || me->query_skill_mapped("strike") != "super-strike"
          || me->query_skill_mapped("parry") != "super-strike")
                 return notify_fail("你现在无法使用「铁蒲扇掌」！\n");

         if( (int)me->query("max_neili") < 2000)
                 return notify_fail("你现在内力太弱，使不出「铁蒲扇掌」。\n");

         if( (int)me->query("neili") < 1500 )
                 return notify_fail("你现在真气太弱，使不出「铁蒲扇掌」。\n");
         
         if( target->query_temp("pushan") )
                 return notify_fail("别那么残忍啦。\n");

         msg = HIW "\n$N你深吸一口气，大喝一声，施出铁掌掌法中的“铁蒲扇掌”击向$n！\n"NOR;
          if ( target->query_con()/3 < random(me->query_con())) {
              msg += HIG"\n$n双掌一并，硬是接下了$N这一掌！\n"NOR;
              if (target->query_str() < me->query_str()) {
                  target->add_temp("apply/strength",-me->query_str());
                  target->set_temp("pushan",me->query_str());
                  target->receive_wound("qi",j*4);
                  target->receive_damage("qi",j*8);
                  msg += HIR"\n只听见喀啦一声，$n的腕骨居然被硬生生的震断了！\n"NOR;
                  
              } else {
                  msg += HIR"\n$n哇地喷出一口鲜血，似乎受了极重的内伤！\n"NOR;
                 
                  target->receive_wound("qi",j*3);
                  target->receive_damage("qi",j*6);
              }
              message_vision(msg, me, target);
              COMBAT_D->report_status(target);
         } else {
             msg += HIY"\n$n见来势凶猛，不敢硬挡，连忙转身避开！\n"NOR;
             msg += HIR"\n岂知$N已经埋伏下厉害后著，连出两掌重手！\n"NOR;
                 message_vision(msg, me, target);
             me->set_temp("tzzf",1);
                 if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->delete_temp("tzzf");
         }               

         me->add("neili", -1500);
         me->start_busy(random(2));
         
         me->start_perform(5,"「铁蒲扇掌」");
         return 1;
 }

