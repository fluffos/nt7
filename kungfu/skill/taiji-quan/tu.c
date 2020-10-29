#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h"

inherit F_SSERVER;

string name() { return HIW "太极图" NOR; }

int perform(object me, object target)
{
        mapping buff;
        object *obs;
        string msg;
        int duration;
        int damage;
        int ap, dp;
        int flag;
        int time;
        int delta;
        int i;
        int p;
        int per;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if( (int)me->query_skill("taiji-quan", 1) < 250 )
                return notify_fail("你的太极拳不够娴熟，难以施展" + name() + "。\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 300 )
                return notify_fail("你的太极神功修为还不够高，难以施展" + name() + "。\n");

        if( (int)me->query_skill("taoism", 1) < 300 )
                return notify_fail("你的道学心法修为还不够高，难以施展" + name() + "。\n");

        if( me->query_skill_mapped("cuff") != "taiji-quan" )
                return notify_fail("你现在没有激发太极拳，难以施展" + name() + "。\n");

        if( me->query_skill_mapped("force") != "taiji-shengong" )
                return notify_fail("你现在没有激发太极神功，难以施展" + name() + "。\n");

        if( query("jing", me)<2000 )
                return notify_fail("你现在精力不够，难以施展" + name() + "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

             if( userp(me)&& !wizardp(me) ) 
        {
                if( (duration = BUFF_D->get_buff_overtime(me, "tjq_tu")) > 0 )
                        return notify_fail(MAG"太极图消耗心神太甚，还需等待"+duration+"秒。\n"NOR);
        }
        
        msg = HIM "$N" HIM "淡然一笑，双手轻轻划了数个圈子，顿时四周的气"
              "流波动，源源不断的被牵引进来。\n\n" NOR;
        message_combatd(msg, me, target);

        per = me->query_skill("taiji-shengong",1)/2000 + me->query_skill("tianwei-zhengqi",1)/240;
        if(per < 1) per = 1;
        if(per > 20) per = 20;
                
        addn("neili", -1000, me);
        addn("jing", -1000, me);
        
        ap = attack_power(me, "cuff") + me->query_skill("taoism", 1);
        delta = ABILITY_D->check_ability(me, "ap_power-tjq-tu");
        if( delta ) ap += ap*delta/100;
        obs = me->query_enemy();
        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp = defense_power(obs[i], "force") + obs[i]->query_skill("count", 1);
                if( ap > dp * 12 / 10 ) 
                {
                        switch (random(3))
                        {
                        case 0:
                                tell_object(obs[i], HIY "恍惚之间你似乎回到了过去的世界，竟"
                                                    "然再无法控制自我，忽然眼前的一切\n"
                                                    "又全然不见，你心头一乱，浑身一阵剧"
                                                    "痛，内力紊乱难以控制！\n" NOR);
                                break;
                        case 1:
                                tell_object(obs[i], HIW "你眼前一切渐渐的模糊起来，好像是到"
                                                    "了仙境，然而你却觉得内息越来越乱，\n"
                                                    "四肢一阵酸痛，几乎要站立不住。\n" NOR);

                                break;
                        default:
                                tell_object(obs[i], HIR "你耳边忽然响起一个霹雳，眼见雷神挥"
                                                    "舞电锤向你打来，你不禁大吃一惊，\n"
                                                    "浑身上下都不听使唤，只有高声呼救。\n" NOR);
                                break;
                        }
                        damage = damage_power(me, "cuff");
                        damage+= me->query_all_buff("unarmed_damage");
                        damage+= damage/100*me->query_skill("tianwei-zhengqi",1);
                        damage+= damage/2000*me->query_skill("taiji-shengong",1);
                        delta = ABILITY_D->check_ability(me, "da_power-tjq-tu"); // 门派ab
                        if( delta ) damage += damage*delta/100;
        
                        if( damage < query("max_qi", obs[i])* (per + random(6)) / 100 )
                            damage = query("max_qi", obs[i])* (per + random(6)) / 100;
                        if( damage > query("max_qi", obs[i]) *2 )
                            damage = query("max_qi", obs[i])*2;                                                   
                        if( damage < 0 ) damage = query("max_qi", obs[i]) /2; 
                                                        
                            obs[i]->receive_damage("qi", damage, me);
                            obs[i]->receive_wound("qi", damage/2, me);
                                                        
                        if( damage < query("max_jing", obs[i])* (per + random(6)) / 100 )
                            damage = query("max_jing", obs[i])* (per + random(6)) / 100;                                             
                        if( damage > query("max_jing", obs[i]) *2 )
                            damage = query("max_jing", obs[i]) *2;                                                 
                        if( damage < 0 ) damage = query("max_jing", obs[i]) /2; 
 
                            obs[i]->receive_damage("jing", damage / 2, me);
                            obs[i]->receive_wound("jing", damage / 4, me);

                        p=query("qi", obs[i])*100/query("max_qi", obs[i]);

                        switch (random(3))
                        {
                        case 0:
                                msg = HIR "只见" + obs[i]->name() +
                                      HIR "手舞足蹈，忘乎所以，忽"
                                      "然大叫一声，吐血不止！\n" NOR;
                                
                                break;
                        case 1:
                                msg = HIR "却见" + obs[i]->name() +
                                      HIR "容貌哀戚，似乎想起了什"
                                      "么伤心之事，身子一晃，呕出数口鲜血！\n" NOR;
                                break;
                        default:
                                msg = HIR + obs[i]->name() +
                                      HIR "呆立当场，一动不动，有如中"
                                      "邪，七窍都迸出鲜血来。\n" NOR;
                                break;
                        }
                        if( !obs[i]->is_busy() )
                                obs[i]->start_busy(3);
                        message("vision", msg, environment(me), ({ obs[i] }));
                        COMBAT_D->report_status(obs[i], 1);
                        addn("neili", -500, obs[i]);
                        flag = 1;
                } else
                {
                        tell_object(obs[i], HIC "你发现眼前的景物似幻似真，连忙"
                                            "默运内功，不受困扰。\n" NOR);
                        addn("neili", -200, obs[i]);
                }
                if( query("neili", obs[i])<0 )
                        set("neili", 0, obs[i]);
        }


        if( !flag )
                message_combatd(HIM "然而没有任何人受了$N"
                               HIM "的影响。\n\n" NOR, me, 0, obs);
        
        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-tjq-tu"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd 
               
        buff = // Perform Cool Dow
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "tjq_tu",
                "attr"   : "curse",
                "name"   : "太极拳·太极图",
                "time"   : time,
                "buff_msg" : "太极图消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
       
        ]);
        BUFF_D->buffup(buff);
        me->start_busy(1+random(2));
        return 1;
}


