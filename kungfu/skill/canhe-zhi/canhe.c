// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

string name() { return HIW "参合剑气" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, slv, clv, dlv, flvl, p;
        int delta, delta2;
        int fmsk = me->query_skill("huitong-tianxia", 1);
        int mlvl = query("level",me);
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用" + name() + "。\n");

        if (clv = (int)me->query_skill("canhe-zhi", 1) < 1800)
                return notify_fail("你的参合指修为有限，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("你现在没有准备使用参合指，难以施展" + name() + "。\n");

        if (flvl = (int)me->query_skill("shenyuan-gong",1) < 1800)
                return notify_fail("你的内功修为太差，难以施展" + name() + "。\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<900 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n"); 
        
        damage = damage_power(me, "finger");
        damage+= query("jiali", me);
        damage+= me->query_all_buff("unarmed_damage");
        damage+= damage / 300 * me->query_str();
        damage/= 100;
        flvl = flvl / 5000;
        if(flvl <1) flvl =1;
        if(flvl >4) flvl =4;
        damage+= damage*flvl;
        damage*= mlvl/10;
        
        slv = target->query_skill("six-finger", 1);
        dlv = target->query_skill("dragon-strike", 1);
        
        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");
        
        ap+= ap/2;
        ap+= ap/1000*fmsk;
        
        delta = ABILITY_D->check_ability(me, "ap_power-chz-canhe"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        delta2 = ABILITY_D->check_ability(me, "da_power-chz-canhe"); // 门派ab
        if( delta2 ) damage += damage*delta2/100;
        
        if(target->query_skill_prepared("finger") == "six-finger"
           && slv > clv + clv /10)
           ap = ap - ap/10;
           
        if(target->query_skill_prepared("strike") == "dragon-strike"
           && dlv > clv + clv /10)
           ap = ap - ap/10;     
        
        msg = HIC "只见$N" HIC "十指分摊，霎时破空声骤响，数股剑气至指尖激"
              "射而出，朝$n" HIC "径直奔去！\n" NOR;

                if (ap / 2 + random(ap) > dp)
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200+fmsk/10,
                                                                                   HIR "\n顿时只听“嗤啦”的一声，$n" HIR
                                                                                   "躲闪不及，剑气顿时穿胸而过，带出一蓬"
                                                                                   "血雨。\n" NOR);
                } else
                {
                        msg += CYN "\n$n" CYN "见$N" CYN "来势汹涌，急忙飞身一跃而"
                                           "起，避开了这一击。\n" NOR;
                }
            
         if(mlvl > 99)
         {  
            msg+= HIW"$N"HIW"默运神元功，真气凝聚指尖，又一招参合剑气！\n"NOR;
            ap = attack_power(me, "finger");
            dp = defense_power(target, "force");
            
            ap += ap/2;

            if( delta ) ap += ap*delta/100;
            if(target->query_skill_prepared("finger") == "six-finger"
               && slv > clv + clv /10)
               ap = ap - ap/10;
               
            if(target->query_skill_prepared("strike") == "dragon-strike"
               && dlv > clv + clv /10)
               ap = ap - ap/10;             
            if (ap / 2 + random(ap) > dp && mlvl > 100)
            {
                damage+= damage/2;
                                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 250+fmsk/5,
                                               HIR "\n只听$n" HIR "一声惨嚎，被$N" HIR
                                               "的剑气刺中了要害，血肉模糊，鲜血迸流不"
                                               "止。\n" NOR);
            } else
            {
                msg += CYN "\n$n" CYN "见$N" CYN "来势汹涌，急忙飞身一跃而"
                           "起，避开了这一击。\n" NOR;
            }
         }
         
         if(mlvl>199)
         {
            msg+= HIY"紧接着，$N"HIY"聚全部真气于指尖，再一招参合剑气！\n"NOR;
            ap = attack_power(me, "finger");
            dp = defense_power(target, "parry");
            
            ap += ap/2;
            if( delta ) ap += ap*delta/100;
            if(target->query_skill_prepared("finger") == "six-finger"
               && slv > clv + clv /10)
               ap = ap - ap/10;
               
            if(target->query_skill_prepared("strike") == "dragon-strike"
               && dlv > clv + clv /10)
               ap = ap - ap/10; 

            if (ap / 2 + random(ap) > dp && mlvl > 200)
            {
                damage+= damage;
                                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300+fmsk/5,
                                               HIR "\n$n" HIR "奋力招架，仍是不敌，$N"
                                               "的" HIR "无形剑气已透体而入，鲜血飞射"
                                               "，无力再战。\n" NOR);
            } else
            {
                msg += CYN "\n$n" CYN "见$N" CYN "来势汹涌，急忙飞身一跃而"
                           "起，避开了这一击。\n" NOR;
            }
        }
        me->start_busy(2+random(2));
        addn("neili", -400-random(100), me);
        message_combatd(msg, me, target);
        if(wizardp(me) && query("id",me)=="mud") tell_object(me,"damage="+damage+"\n");
        return 1;
}

