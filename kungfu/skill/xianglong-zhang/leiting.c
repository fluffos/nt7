//leiting.c  「雷霆一击」
//last modified by suncity may 30th,2002
#include <ansi.h>

inherit F_SSERVER;
#define PNAME "「"+HIY"雷"NOR+HIC"霆"NOR+HIG"一"NOR+HIR"击"NOR+"」"
int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
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

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用雷霆一击。\n");

        fskill = "huntian-qigong";
        bskill = "strike";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(fskill)+"火候不够，使不出"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(sskill)+"不够熟练，不会使用"+PNAME+"。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力修为还不够高。\n");

        msg = HIC "$N默运混天气功，施展出「"+HIY"雷"NOR+HIC"霆"NOR+HIG"一"NOR+HIR"击"NOR+"」，全身急速转动起来，越来越快，就犹如一股旋风，骤然间，$N已卷向正看得发呆的$n。\n"NOR;  

        if( random(query("combat_exp", me))>query("combat_exp", target)/3 )
        { 
                me->start_busy(3);
                target->start_busy(random(3));

                damage = (int)me->query_skill(bskill, 1)*2+(int)me->query_skill("force", 1);

                damage = damage + random((int)damage/2);

                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                addn("neili", -500, me);
                msg += HIR"$n只见一阵旋风影中陡然现出$N的双拳，根本来不及躲避，被重重击中，五脏六腑翻腾不休，口中鲜血如箭般喷出！！！\n"NOR;
        }
        else
        {
                me->start_busy(1);
                addn("neili", -200, me);
                msg += HIG"可是$p看破了$P的企图，闪在了一边。\n"NOR;
        }
        message_combatd(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                损伤对方气血

        出手要求：
                混天气功100级
                降龙十八掌100级
                内力500
HELP
        );
        return 1;
}
