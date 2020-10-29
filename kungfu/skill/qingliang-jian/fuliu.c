//清风拂柳
//edit by gladiator

#include <ansi.h>
#include <combat.h>


#define FULIU HIG "「清风拂柳」" NOR
inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon; 

        if ( !target ) target = offensive_target(me);
        weapon=query_temp("weapon", me);

        if( !userp(me) && me->query_skill("qingliang-jian")<100 && !query("can_perform/qingliang-jian/fuliu", me) )
              return notify_fail("你使用的外功中没有这种功能！\n");
              
        if ( !target || !target->is_character() || !me->is_fighting(target) )
              return notify_fail(FULIU + "只能对战斗中的对手使用。\n");

        if ( (int)me->query_skill("qingliang-jian", 1) < 80 )
              return notify_fail("你的清凉剑法不够熟练，不能使用" + FULIU + "。\n");

        if ( (int)me->query_skill("force", 1) < 80 
         || (int)me->query_skill("shaolin-xinfa",1 ) < 80)
              return notify_fail("你是否应该在内功修为上多下点功夫。\n");

        if( query("max_neili", me)<1000 )
              return notify_fail("你的内力修为还不够高。\n");

        if( query("neili", me)<300 )
              return notify_fail("你的内力不够使用" + FULIU + "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
        || me->query_skill_mapped("sword") != "qingliang-jian" )
              return notify_fail("你的剑法不是清凉剑。\n");
        
        if (! living(target)) 
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n"); 
 
        msg = HIG "\n$N暗运真气，衣袖慢慢鼓了起来，犹似吃饱了风的帆篷一般，"
                  "然而却又似一阵清风般让人感到舒服和安逸，\n"
                  "轻轻一剑，就象一阵清风吹落的一片杨柳叶，划向$n。\n" NOR;

        if( random(query("combat_exp", me))>query("combat_exp", target)/3 )
        { 
                me->start_busy(3);
                target->start_busy(random(2));

                damage = (int)me->query_skill("qingliang-jian", 1) + 
                         (int)me->query_skill("dodge", 1) / 2;
                         
                damage = damage /2 + random(damage);
//                target->receive_damage("qi", damage * 2)
//                target->receive_wound("qi", damage)
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, damage / 2,
                        GRN "$n被这招" + FULIU + GRN "轻轻一带，胸口划出一条长长的伤口，"
                           "立时鲜血狂喷而出！\n" NOR);
   
                message_vision(msg, me, target);
                COMBAT_D->report_status(target);    
                return 1;
        } else
        {
                me->start_busy(3);
       
                msg += HIG"$n看得分明，连忙提气纵身，以跳离了$N的剑气范围。\n"NOR;
        }
                
        addn("neili", -150, me);
        message_vision(msg, me, target);

        if ( !target->is_fighting(me)) target->fight_ob(me);
        return 1;
}
