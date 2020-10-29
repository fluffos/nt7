// dashouyin dashou-yin perform
// by dubei

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
      string msg, dodge_skill;                                
      int damage, jiali, attack, defense, p;
      object armor;


      if (me->query_skill("buddhism", 1) < 300)
           return notify_fail("你的佛法修为不足，无法施展该绝招！\n");
      
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target) )
           return notify_fail("「大手印」只能在战斗中对对手使用。\n");        
      
      if( (int)me->query_skill("dacidabei-shou",1) < 120 )
           return notify_fail("你的大慈大悲手不够娴熟，不会使用「大手印」！\n");
      
      if( (int)me->query_skill("hand",1) < 120 )
           return notify_fail("你的基本手法不够娴熟，不会使用「大手印」！\n");

      if( (int)me->query_str() < 35 )
           return notify_fail("你的臂力不够强，不能使用「大手印」！\n");
      
      if( query("max_neili", me)<1200 )
           return notify_fail("你的内力太弱，不能使用「大手印」！\n");
      
      if( query("neili", me)<800 )
           return notify_fail("你的内力太少了，无法使用出「大手印」！\n");   

      if( (int)target->query_condition("dashouyin"))
           return notify_fail("对方早已身中「大手印」绝技了！\n");   
      
      if (me->query_skill_prepared("hand") != "dacidabei-shou")
           return notify_fail("你还没有准备大慈大悲手，无法施展「大手印」！\n");   
          
      if( objectp(query_temp("weapon", me)) )
           return notify_fail("你必须空手使用「大手印」！\n");                                                                              
      jiali=query("jiali", me)+1;
      attack=query("combat_exp", me)/1000;
      attack += me->query_skill("hand");
      attack+=query("neili", me)/5;
      defense=query("combat_exp", target)/1000;
      defense += target->query_skill("dodge");
      defense+=query("neili", target)/7;
      attack = (attack+random(attack+1))/2;
      
      damage = me->query_skill("dacidabei-shou", 1)/40 * jiali;
      if(damage > 1500) damage = 1500;
      
      message_vision(HIR "\n$N突然面色通红，低声默念禅宗真言，双臂骨节一阵爆响，猛然"
                     "腾空而起，伸手向$n胸前按去，好一式「大手印」！\n"NOR,me,target);
 
      if( attack > defense ) { 
               if( objectp(armor=query_temp("armor/cloth", target) )
                   && query("armor_prop/armor", armor)<200
                  && damage > 500){
                        message_vision(HIY"只见这斗大的手印正好印在$N的$n"HIY"上，越变越"
                                       "大，竟将它震得粉碎，裂成一块块掉在地上！\n"NOR, target, armor);
                        armor->unequip();
                        armor->move(environment(target));
                        set("name", "破碎的"+query("name", armor), armor);
                        set("value", 0, armor);
                        set("armor_prop/armor", 0, armor);
                        target->reset_action();
                        }
               tell_object(target, RED"你只觉得霍的胸口一阵剧痛，已经被拍中了前胸！\n"NOR);
               target->receive_damage("qi", damage,  me);
         target->receive_wound("qi", damage/3, me);
         p=query("qi", target)*100/query("max_qi", target);

         msg = "( $n"+eff_status_msg(p)+" )\n";
         message_vision(msg, me, target);
         addn("neili", -jiali, me);
              }
      else {
               dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);
         }
      addn("neili", -200, me);
      me->start_busy(2+random(2));            
      return 1;
}

 