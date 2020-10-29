// Last Modified by Lonely on Jul. 15 2001
// yinyang.c

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "阴阳掌"
int perform(object me, object target)
{
        string msg;
        int skill, damage;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname))
   return notify_fail("你所使用的外功中没有这种功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能对战斗中的对手使用。\n");
                
        if( query_temp("weapon", me) )
                return notify_fail("你只能空手出绝招。\n");

        fskill = "hanbing-zhenqi";
        bskill = "strike";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(fskill)+"修为不够，不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(sskill)+"修为不够，不能使用"+PNAME+"。\n");

        if( query("max_neili", me)<600 )
                return notify_fail("你的内力修为不够。\n"); 

        if( query("neili", me)<400 )
                return notify_fail("你的内力不够。\n"); 

        skill = me->query_skill(bskill, 1);
        msg = HIY"使出大嵩阳掌的绝技「阴阳掌」，双掌远远一推一拉，$n顿觉一股\n"HIB"寒气"HIY"袭上身来，登时机伶伶打了个冷战。$n只一呆，一股"HIR"炙热的掌风"HIY"跟着扑到，击得$n几乎窒息，身子晃了几晃。\n";

        damage=query("jiali", me)*3+100;

        if(random(me->query_skill(bskill, 1)) > target->query_skill("parry",1)/3)
        {
          if( query("jiali", me)*10>query("neili", target) )
          {
                        msg += HIR"掌力击在$n胸口，打得$n身子飞了出去。\n"NOR;
                        target->receive_damage("qi", damage,me);
                        target->receive_damage("jing", damage,me);
                        me->start_busy(1);
                        addn("neili", -100, me);
          } 
          else
          {
                        msg += HIB"这一阴一阳两股掌力打在$n身上，$n体内真气自然而然生出相应之力，护住心脉内脏，不受损伤。但霎时间全身剧震，说不出的难受。\n"NOR;
                        target->receive_damage("qi", (int)(damage/2),me);
                        target->receive_damage("jing", damage,me);
                        me->start_busy(2);
                        addn("neili", -200, me);
          }
        }
        else 
          {     
                  msg+=HIG "结果$p看破了$P的企图，身行后跃，避开了$P的掌力。\n" NOR;
                me->start_busy(3);
                 addn("neili", -200, me);
          }
        message_combatd(msg, me, target);
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                损害敌手气血

        出手要求：
                寒冰真气120级
                大嵩阳掌120级
                内力修为600
                内力400
HELP
        );
        return 1;
}
