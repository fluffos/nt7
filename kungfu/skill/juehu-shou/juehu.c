// juehu.c 虎爪绝户手「绝户」
// by Lonely

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        int damage, ap, dp;
        string msg, pmsg;
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("神功伤敌只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用「绝户」神功！\n");  
                
        if( (int)me->query_skill("juehu-shou", 1) < 100 )
                return notify_fail("你的虎爪绝户手不够娴熟，不会使用「绝户」神功\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 100 )
                return notify_fail("你的太极神功不够高，不能用「绝户」神功伤敌。\n");

        if( query("shen", me)<10000 )
                return notify_fail("你邪气太重，无法使出「绝户」招式。\n");

        if( query("neili", me)<400 )
                return notify_fail("你现在内力太弱，不能使出「绝户」招式。\n");

        msg = BLU "$N默运神功，脸色白得吓人，突然使出虎爪绝户手的最后一击「绝户」，企图当场把$n废于抓下。\n" NOR;
        
        
        addn("shen", -8000, me);
        me->want_kill(target);
                              
        ap = attack_power(me, "claw"); 
        dp = defense_power(target, "force"); 

        if (ap / 2 + random(ap) > dp) 
        {       
                damage = damage_power(me, "claw");
                addn("neili", -300, me);
                pmsg = RED "结果$N一击命中，$n只感到下体一阵刺痛，体内精元不断外泄，顿时觉的四肢无力，两腿不停颤抖。\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50, pmsg);

                me->start_busy(3);
                target->start_busy(3);                
                
        } else 
        {
                addn("neili", 150, me);
                msg += CYN "可是$p" CYN "看破了$P" CYN "的狠毒企图，向旁跳开数步，躲开了$P" CYN "的凌厉一击！\n" NOR;
                me->start_busy(4);
        }
        
        message_combatd(msg, me, target);
        
        if (damage > 200)
        {
                target->apply_condition("juehu_hurt",(500*query("age", target)));
                if( query("gender", target) == "男性" )
                {
                        message_combatd(HIW "$N突然觉的丹田内的精元已流失迨尽，心里一阵难过，知道自己有一段时间不能行欢做乐了!\n" NOR, target);
                } else
                {
                        if( query("gender", target) == "女性" )
                                message_combatd(HIW "$N被你一击命中，，不禁既羞又怒，见$n竟对一女流之辈也用此阴毒招数！\n"NOR,
                                                target,me);
                        else
                                message_combatd(HIW "$N虽然击中$n的要害，但感觉受力甚轻，似乎已无要害可言!\n"NOR,
                                me,target);
                }
          
        }
        
        if (! target->is_killing(me))
                target->kill_ob(me);
        return 1;
}
