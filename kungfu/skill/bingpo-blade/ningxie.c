// ningxie.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
//inherit F_CLEAN_UP;

void remove_effect(object me,object target, int dodge_amount,int attack_amount);
void check(object me,object target,int dodge_amount,int attack_amount);
void ningxie_result(object me, object target);

int perform(object me, object target)
{
        int skill,skill_blade, skill_dodge, dodge_amount,attack_amount;
        int blade_skill,bingpo_skill;
        object weapon;

        weapon=query_temp("weapon", me);
        skill = me->query_skill("bingxue-xinfa",1);
        blade_skill= me->query_skill("blade",1);
        bingpo_skill= me->query_skill("bingpo-blade",1);
        if( skill > 250 ) skill=250;
        skill_dodge = me->query_skill("dodge");
        skill_blade = me->query_skill("force");
        attack_amount=skill_blade*(2+random(5))/2;
        dodge_amount=skill_dodge*(3+random(5))/2; 
                
                       
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展「凝血」？\n");

        if(!me->is_fighting())
               return notify_fail("「凝血」只能在战斗中使用！\n");
                       
        if( skill < 100 )  return notify_fail("你的冰雪心法修为不够。\n");
        if( blade_skill < 100 )  return notify_fail("你的基本刀法未够纯熟。\n");
        if( bingpo_skill < 100 )  return notify_fail("你的冰魄寒刀未够纯熟。\n");
                
        
        if( query_temp("ningxie", me) )
          {remove_effect(me, target, dodge_amount, attack_amount);return 1;}
        
        if( query("neili", me)<skill )
                return notify_fail("你的内力不够。\n");
        
      

        addn("force", -skill, me);
        message_vision(HIW "$N把冰雪心法在体内运转，然后徐徐注入"+weapon->name()+HIW"中。
$N手中"+weapon->name()+HIW"所到处带起了一阵轻烟，方圆几丈内的空气好象都凝聚起来！\n" NOR, me);
        set_temp("ningxie", 1, me);
        set_temp("ningxie_effect", 0, target);
       
        //要perform ningxie当然要有所代价
        addn_temp("apply/attack", -attack_amount, me);
        addn_temp("apply/dodge", -dodge_amount, me);
        
        call_out("remove_effect",skill,me,target,dodge_amount,attack_amount);
        call_out("ningxie_result",5,me,target);
        call_out("check", 1, me,target,dodge_amount,attack_amount);
        return 1;
}


void check(object me,object target, int dodge_amount,int attack_amount)
{           
        object weapon;
        
        if( !living(target) || !present(query("id",target), environment(me)) )  
                remove_effect(me, target, dodge_amount, attack_amount);

        else if( !present(query("id", target),environment(me) )
                || !me->is_fighting(target) || !me->is_fighting() ) 
                remove_effect(me, target, dodge_amount, attack_amount);
        
        
        else if (me->query_skill_mapped("force") != "bingxue-xinfa"
                  || !objectp(weapon=query_temp("weapon", me) )
                  || (query("apply/skill_type", weapon) != "blade"
                      && query("skill_type", weapon) != "blade" )
                 ||  me->query_skill_mapped("blade") != "bingpo-blade" )     
             remove_effect(me, target, dodge_amount, attack_amount);
        
        else call_out("check", 1, me,target,dodge_amount,attack_amount);
             
}


void remove_effect(object me,object target, int dodge_amount,int attack_amount)
{
        if(!me) return;
        remove_call_out("check");
        remove_call_out("remove_effect");
        remove_call_out("ningxie_result");
        addn_temp("apply/dodge", dodge_amount, me);
        addn_temp("apply/attack", attack_amount, me);
        delete_temp("ningxie", me);
        tell_object(me, GRN"你将冰雪心法收回丹田。\n"NOR);
        message_vision(HIY"周围寒气慢慢散开了。\n"NOR,me);
        tell_object(target, HIY"你觉得暖和起来了。\n"NOR);
        delete_temp("ningxie_effect", target);
}


void ningxie_result(object me, object target)
{        
           int afp,vfp,mod_val;
           object weapon;
           string str;
           weapon=query_temp("weapon", me);
           
            message_vision(HIB"\n随着$N手中"+weapon->name()+HIB"的舞动，周围的空气越来越冷了。\n"NOR,me);
            
            afp = COMBAT_D->skill_power(me, "neili", SKILL_USAGE_DEFENSE);
            if( afp < 1) afp = 1;
            vfp = COMBAT_D->skill_power(target, "neili", SKILL_USAGE_ATTACK);
            if( vfp < 1 ) vfp = 1;
            if( query("neili_factor", me) && (query("neili", me)>query("neili_factor", me)) )
                   mod_val=(100+query("neili_factor", me)/10);
                   else mod_val=100;
            if( afp > 1000000 )     mod_val = afp / 100 * (100 + mod_val);
                     else   mod_val = (100 + mod_val) * afp / 100;
            if( mod_val < 1 ) mod_val = 1;
            
            if( random(mod_val + vfp) < vfp )
                  {message_vision(YEL"$N运气一转，全不把寒冷放在心上！\n"NOR,target); 
                   addn_temp("ningxie_effect", -1, target);
                   if( query_temp("ningxie_effect", target)<0)set_temp("ningxie_effect", 0, target);
                  }      
                
                else {if( query("force_factor", me) && (query("force", me)>query("force_factor", me)) )
                                 addn("force", -query("force_factor", me), me);
                        
                        switch(query_temp("ningxie_effect", target) )
                          {
                                  case 0: {message_vision(WHT"$N打了一个寒颤。\n"NOR,target);
                                           set_temp("ex_ningxie", 7, me);
                                           COMBAT_D->do_attack_damage(me,target,query_temp("weapon", me));
                                         COMBAT_D->report_status(target);
                                         target->receive_damage("jing",random(me->query_skill("force")));
                                         COMBAT_D->report_sen_status(target);
                                         addn_temp("ningxie_effect", 1, target);
                                         delete_temp("ex_ningxie", me);
                                         break;
                                        }
                                        
                                case 1: { message_vision(WHT"$N冷的浑身颤抖！\n"NOR,target);
                                          set_temp("ex_ningxie", 8, me);
                                          COMBAT_D->do_attack_damage(me,target,query_temp("weapon", me));
                                          COMBAT_D->report_status(target);
                                          target->receive_damage("jing",random(me->query_skill("force")));
                                          COMBAT_D->report_sen_status(target);
                                          addn_temp("ningxie_effect", 1, target);
                                          delete_temp("ex_ningxie", me);
                                          break;
                                         }    
                                
                                case 2:  {message_vision(WHT"$N冷得脸色惨白！\n"NOR,target);
                                          set_temp("ex_ningxie", 9, me);
                                          COMBAT_D->do_attack_damage(me,target,query_temp("weapon", me));
                                          COMBAT_D->report_status(target);
                                          target->receive_wound("jing",random(me->query_skill("force")));
                                          COMBAT_D->report_sen_status(target);
                                          addn_temp("ningxie_effect", 1, target);
                                          delete_temp("ex_ningxie", me);
                                          break;
                                         }    
            
                                case 3:  {message_vision(WHT"$N冷得像一条冰棍了！\n"NOR,target);
                                          set_temp("ex_ningxie", 10, me);
                                          COMBAT_D->do_attack_damage(me,target,query_temp("weapon", me));
                                          COMBAT_D->report_status(target);
                                          target->receive_wound("jing",random(me->query_skill("force")));
                                          COMBAT_D->report_sen_status(target);
                                          delete_temp("ex_ningxie", me);
                                         }                        

                        }
                    if (query("max_qi",target)<0 || query("max_jing",target)<0 || (!living(target) && ((query("jing",target)<0) || query("qi",target)<0)) )   
                       {str=target->name()+"被"+me->name()+"手中"+weapon->name()+HIM"所带出的寒气活活冻死了，听说连尸体也青一块紫一快的！"NOR;
                        CHANNEL_D->do_channel(me, "rumor",str);
                        target->die();
                        delete_temp("last_channel_msg", me);
                       }
                    }
 
             if( query_temp("ningxie", me))call_out("ningxie_result",3+random(6),me,target);
}
