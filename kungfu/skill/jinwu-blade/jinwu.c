
// jinwu.c 金乌堕地

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIR"金乌堕地"NOR; } 

int perform(object me,object target)
{
        string msg;
        object weapon;
        int ap, dp, qi_wound;
        int temp;
        string skill, fskill,bskill;

        if( !objectp(target) ) {target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||       
                !me->is_fighting(target) ||
                !living(target) )
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if (!objectp(weapon = query_temp("weapon",me)) ||
                query("skill_type", weapon) != "blade")
                return notify_fail("你使用的武器不对。\n");
        
       skill  = "jinwu-blade";     
        fskill = "bingxue-xinfa";
        bskill = "blade";

        if( (int)me->query_skill(skill, 1) < 200 )
                return notify_fail("你的"+to_chinese(skill)+"等级不够, 不能使用"+name()+"。\n");
                
        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(fskill)+"等级不够, 不能使用"+name()+"。\n");

        if( me->query("max_neili") < 1000 )
                return notify_fail("你的内力修为不够，无法运用「"+HIR"金乌堕地"NOR+"」！\n");

        if( me->query("neili") < 400 )
                return notify_fail("你的内力不够，无法运用「"+HIR"金乌堕地"NOR+"」！\n");

        msg = HIY"$N纵身跃起,使出"+HIR"「金乌堕地」"HIY"，挥舞"NOR+weapon->name()+HIY"从半空中挥刀直劈下来，\n"
              "刀锋离地尚有数尺，地下已是尘沙飞扬，败草落叶被刀风激得团团而舞，\n将$n逃遁退避的空隙封的严严实实。\n"NOR;
        message_combatd(msg, me, target);
        msg = "";

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");
        if (target->query_skill_mapped("parry") == "xueshan-sword")
        {
                msg += HIR "$n" HIR "慌忙中忙以"HIW"雪山剑法"HIR"作出抵挡，哪知$N"
                       HIR "刀法竟似雪山剑法克星般，\n" + weapon->name() +
                       HIR "刀芒霎时又暴涨数倍，完全封锁$n" HIR "的所"
                       "有剑招！\n" NOR;
                ap = ap * 2;
                temp = 1;
        }       

        if( random(ap) + ap / 2 > dp )
        {
                if(userp(me)) me->add("neili",-250);
                msg += HIC"$n避无可避，只觉一股刚猛之极的劲风扑面而来，使人直欲窒息。\n"
                        "$n极力后退隔挡，却只见"NOR""+weapon->name()+""HIC"刀光一闪，毫不停息，一刀正中面门。\n"NOR;
                qi_wound = damage_power(me, "blade")+me->query_str()*10;
                qi_wound *= 2;
                if (temp != 1) //对付非雪山门派
                {
                        qi_wound = random(qi_wound);
                        if(qi_wound > query("qi", target)) qi_wound = 100;
                }
                target->receive_damage("qi", qi_wound);
                target->receive_wound("qi", query("max_qi", target)/3);
                target->start_busy(2+random(1));
                me->start_busy(1+random(1)); 
        }
        else
        {
                if( userp(me) ) me->add("neili",-100);
                msg += HIW"可是$n轻轻往旁边一闪，避过了$N这必杀的一刀。\n"NOR;
                me->start_busy(2+random(2));
        }
        message_combatd(msg, me, target);
        return 1;
}

