// Last Modified by Lonely on Aug. 25 2001
// zhouyu.c 暴风骤雨

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "「暴风骤雨」"
int perform(object me, object target)
{
        string msg;
        int skill, damage, ap, dp;
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
                return notify_fail("只有空手才能施展「暴风骤雨」。\n");

        fskill = "panshi-shengong";
        bskill = "strike";
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(fskill)+"修为不够，不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(sskill)+"修为不够，不能使用"+PNAME+"。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的内力修为不够。\n"); 

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够。\n"); 

        addn("neili", -100, me);

        if( random(query("max_neili", me))<50 )
        {
                write("糟糕，没成功！\n");
                return 1;
        }
        
        skill = me->query_skill(bskill, 1);
                msg = HIC"\n$N"HIC"一反平常快活逍逸的神情，口中大喝了一声，施展出「暴风骤雨」，双掌上下翻飞，\n$n只觉得四周都是$N"HIC"双掌的影子，根本不知如何招架，更不用说躲闪了！\n\n" NOR;

        ap = skill;
        ap=(ap*ap*ap/(4*400))+query("qi", me);
        ap=ap*250+query("combat_exp", me);
        dp = target->query_skill("parry",1);
        dp=(dp*dp*dp/(4*400))+query("qi", target);
        dp=dp*250+query("combat_exp", target);
        if( random(ap + dp) > dp )
        {
                  damage = query("max_neili",me) / 10 + random(query("eff_qi",me) /50); 
                  damage -= query("max_neili",target) / 10 + random(query("eff_qi",target) / 50); 
                if( damage > 0 )
                {
                        msg += HIC "结果一掌结结实实全部拍中了$n"HIC"，几乎把$n"HIC"的骨头都震散了！\n" NOR;
                        damage +=random((damage*(int)me->query_skill("strike"))/50);
                        target->receive_damage("jing", damage, me);
                        target->receive_wound("jing", damage/4, me);
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/3, me);
                }
                else
                {
                        msg += HIC "结果被$n"HIC"以内力反激，$N"HIC"反而自受其苦，双手受伤不轻！\n" NOR;
                        damage -=random((-damage*(int)target->query_skill("strike"))/80);
                        me->receive_damage("jing", -damage, target);
                        me->receive_damage("qi", -damage, target);
                        me->improve_skill("kuaihuo-strike", 1, 1);
                }
        }
        else msg += "但是被$n躲开了。\n";

        message_combatd(msg, me, target);
        if( damage > 0 ) COMBAT_D->report_status(target);
        else if( damage < 0 ) COMBAT_D->report_status(me);

        if( !target->is_fighting(me) ) target->fight_ob(me);

        me->start_busy(3);
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                损害敌手精气和气血，但也可能被对手反震受创

        出手要求：
                磐石神功50级
                快活十三掌50级
                内力修为300
                内力200
HELP
        );
        return 1;
}

