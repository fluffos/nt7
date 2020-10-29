#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "佛光普照" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage, flagremote = 0;
        int lvl_jingxin = me->query_skill("jingxin", 1);
        int lvl_emjy = me->query_skill("emei-jiuyang", 1);//不须要求mapped
        int lvl_ngxy = me->query_skill("force-cognize", 1);
        int time;
        mapping buff;
        int flagclaw = 0;
        object *obs, newtarget;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能施展" + name() + "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的内功的修为不够，无法施展" + name() + "。\n");

        if (me->query_skill("piaoxue-zhang", 1) < 180)
                return notify_fail("你的飘雪穿云掌修为不够，无法施展" + name() + "。\n");

        if( query("neili", me)<1000 || query("max_neili", me)<3500 )
                return notify_fail("你的真气不够，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "piaoxue-zhang")
                return notify_fail("你没有激发飘雪穿云掌，无法施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "piaoxue-zhang")
                return notify_fail("你没有准备飘雪穿云掌，无法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

//        if( userp(me) ) 
//        {
                if( (time = BUFF_D->get_buff_overtime(me, "emaq_piaoxuezhao")) > 0 )
                        return notify_fail(MAG"佛光普照消耗心神太甚，还需等待"+time+"秒。\n"NOR);
//        }

        msg = HIY "$N" HIY "运起全身功力，顿时真气迸发，全身骨骼噼啪作"
              "响，猛然一掌向$n" HIY "\n全力拍出，力求一击毙敌，正是一"
              "招「佛光普照」。\n" NOR;

        ap = attack_power(me, "strike") +
                                me->query_skill("force") +
                                me->query_skill("martial-cognize") +
                                me->query_skill("force-cognize") +
                                me->query_skill("mahayana") * 3 + 
                                me->query_str()*(100+query("level",me));
        dp = defense_power(target, "dodge") +
                                target->query_skill("force") +
                                target->query_skill("martial-cognize") +
                                target->query_skill("force-cognize") +
                                me->query_con()*100;
        ap = ap + ap * lvl_jingxin / 600;
        ap += ap*(ABILITY_D->check_ability(me, "ap_power-pxz-zhao"))/100; 
        if (target->is_busy()) ap += ap / 6;
        if (BUFF_D->check_buff(me, "ljz_zhixin")) ap += ap / 8;
        
        if( (userp(me) && !query("yuanshen", me)) && 
                (target->query_skill_mapped("force") == "jiuyang-shengong") ) 
                {
                addn("neili", -1000, me);
                me->start_busy(5);
                msg += HIW "只听轰然一声巨响，$n" HIW "已被一招正中，可$N"
                       HIW "只觉全身内力犹如江河入\n海，又如水乳交融，登"
                       "时消失得无影无踪。\n" NOR;
                }
        else 
        if ((target->query_skill_mapped("force") == "jiuyang-shengong") && random(5)<2)//元神后40%
        {
                addn("neili", -1000, me);
                me->start_busy(5);
                msg += HIW "只听轰然一声巨响，$n" HIW "已被一招正中，可$N"
                       HIW "只觉全身内力犹如江河入\n海，又如水乳交融，登"
                       "时消失得无影无踪。\n" NOR;
        } 
        else
        if (ap * 4 / 5 + random(ap) > dp)
        {
                        damage = damage_power(me, "strike");// + me->query_skill("mahayana", 1);
                        if (BUFF_D->check_buff(me, "ljz_zhixin") && BUFF_D->check_buff(me, "ljz_fengyun") && BUFF_D->check_buff(me, "ljz-niepan")) 
                                damage += me->query_all_buff("damage");
                        damage += damage * query("jiali", me) / 5000; 
                        damage += damage * lvl_jingxin / 150;
                 if(!userp(me) && userp(target)) {
                       damage = damage / query("level", target);
                 }
                        addn("neili", -1000, me);
                
                        if (!target->is_busy())
                                target->start_busy(1);
                       
                        time = 4;
                        if( BUFF_D->check_buff(me, "ljz_fengyun") ) time -= 1;
                        if ( BUFF_D->check_buff(me, "ljz-niepan") ) time -= 1;
                        me->start_busy(1 + random(time));
                        
                        if (lvl_emjy > 200 && (!userp(me) || query("yuanshen", me))) //by redl 元神大招效果
                        {
                                damage += damage * lvl_emjy / 5000;
                                damage += damage * lvl_ngxy / 10000;
                                if (lvl_emjy > 1000 && lvl_ngxy > 1000 && !userp(target)) damage *= lvl_emjy / 1000 + lvl_ngxy / 1000;
                                if (lvl_emjy > 5000 && lvl_ngxy > 3500) {
                                        if ((lvl_emjy / 150) > 85) {//12000lv满85% REMOTE_ATTACK
                                                if (random(100) < 86) flagremote = 1;
                                        } else {
                                                if (random(100) < (lvl_emjy / 150)) flagremote = 1;
                                        }
                                        damage += damage / 8;
                                        if (lvl_emjy > 8000 && lvl_ngxy > 5000) damage += damage / 7;
                                        if (lvl_emjy > 12000 && lvl_ngxy > 8000) damage += damage / 6;
                                        if (lvl_emjy > 16000 && lvl_ngxy > 12000) damage += damage / 5;
                                }
                                if ( 
                                        (int)me->query_skill("claw", 1) > 1000 && 
                                        (int)me->query_skill("jiuyin-baiguzhao", 1) > 1000 && 
                                        (me->query_skill_mapped("claw") == "jiuyin-baiguzhao") && 
                                        random( 2 + (int)(me->query_skill("jiuyin-baiguzhao", 1) / 3333) )
                                ) {
                                        switch(query("character", me) )
                                        {
                                                case "心狠手辣":
                                                        msg += NOR CYN "$N" NOR CYN "桀桀怪笑，虚晃一掌，倏的冲$n"
                                                        NOR CYN "头顶抓下。\n" NOR;
                                                        break;
                                                case "阴险奸诈":
                                                        msg += NOR CYN "$N" NOR CYN "冷笑数声，虚晃一掌，飞向$n"
                                                        NOR CYN "头顶抓下。\n" NOR;
                                                        break;
                                                default:
                                                        msg += NOR CYN "$N" NOR CYN "扬声吐气，虚晃一掌，奋力向$n"
                                                        NOR CYN "头顶抓下。\n" NOR;
                                                        break;
                                        }                                                                               
                                        if ( random((int)me->query_skill("jiuyin-baiguzhao", 1) * (query("jiali", me) + 1)) > (int)target->query_skill("parry", 1) / 2 && 
                                                        query("max_neili", me) > ( (userp(target)) ? query("max_neili", target) * 3 : query("max_neili", target) / 100 )
                                        ) {
                                                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, ( (damage > query("max_qi", target)) ? query("max_qi", target) + 1 : damage  ), 
                                                90 + (int)me->query_skill("jiuyin-baiguzhao", 1) /50, 
                                                HIR "$N" HIR "这一爪来势好快，正抓中$n"
                                                HIR "的檀中大穴，$n" HIR
                                                "一声惨叫，软绵绵的瘫了下去。\n" NOR);
                                                flagclaw = 1;
                    } else {
                                                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + (int)me->query_skill("jiuyin-baiguzhao", 1) /50, 
                                                HIR "$n" HIR "连忙躲闪，但“扑哧”一声，$N"
                                                HIR "五指正插入$n" HIR "的手背。\n" NOR);
                    }
                                                target->affect_by("jy_poison",
                                                ([ "level" : query("jiali", me) / 50 + 200 + query("level", me) * 10,
                                                        "id":query("id", me),
                                                        "duration" : (int)me->query_skill("jiuyin-baiguzhao", 1) / 10 + query("level", me) ]));
                                                msg += NOR BLU "$n" BLU "突然只膝弯曲，身子慢慢垂下，口中发出似人似鬼的荷荷之声。\n" NOR; 
                }
                                                                
                                if (flagclaw) {
                                        obs = me->query_enemy();
                                        obs = obs - ({target});
                                        if (!obs || !arrayp(obs) || !sizeof(obs))
                                                flagclaw = 0;
                                        else {  
                                                newtarget = obs[random(sizeof(obs))];
        ap = attack_power(me, "strike") +
                                me->query_skill("force") +
                                me->query_skill("martial-cognize") +
                                me->query_skill("force-cognize") +
                                me->query_skill("mahayana") * 3 + 
                                me->query_str()*(100+query("level",me));
        dp = defense_power(newtarget, "dodge") +
                                newtarget->query_skill("force") +
                                newtarget->query_skill("martial-cognize") +
                                newtarget->query_skill("force-cognize") +
                                me->query_con()*100;
        ap = ap + ap * lvl_jingxin / 600;                                               
        ap += ap*(ABILITY_D->check_ability(me, "ap_power-pxz-zhao"))/100; 
        if (newtarget->is_busy()) ap += ap / 6;
        if (BUFF_D->check_buff(me, "ljz_zhixin")) ap += ap / 8;
                                            if (ap + random(ap) < dp)
                                                        flagclaw = 0;
                                        }
                                }
                                        if (flagclaw) {
                                                message_combatd(msg, me, target);
                                                target = newtarget;
                                                                                        if (flagremote && !random(3)){
                                                                                                if (damage<query("eff_qi", target)/5) {
                                                                                                        target->receive_damage("qi", query("eff_qi", target)/5);
                                                                                                        target->receive_wound("qi", query("eff_qi", target)/5);
                                                                                                } else {
                                                                                                        target->receive_damage("qi", damage);
                                                                                                        target->receive_wound("qi", damage);
                                                                                                }
                                                                                        }
                                                msg = COMBAT_D->do_damage(me, target, (flagremote ? REMOTE_ATTACK : UNARMED_ATTACK), damage, 135 + lvl_jingxin /25 + lvl_emjy / 20, 
                                                        NOR CYN "$N" NOR CYN "大喝一声，双袖鼓荡起" + ((flagremote) ? BLINK : NOR) + HIW "峨眉九阳"  
                                                        NOR CYN + ((flagremote) ? "螺旋透劲" : "劲气") + "，顺势往旁一推。\n" NOR
                                                        HIR "只听轰然一声巨响，$n" HIR "被$N"
                                                        HIR "一招正中，身子便如稻草般平平飞出"
                                                        "，重\n重摔在地下，呕出一大口鲜血，动"
                                                        "也不动。\n" NOR);
                                        } else {
                                                                                        if (flagremote && !random(3)){
                                                                                                if (damage<query("eff_qi", target)/5) {
                                                                                                        target->receive_damage("qi", query("eff_qi", target)/5);
                                                                                                        target->receive_wound("qi", query("eff_qi", target)/5);
                                                                                                } else {
                                                                                                        target->receive_damage("qi", damage);
                                                                                                        target->receive_wound("qi", damage);
                                                                                                }
                                                                                        }
                                                msg += COMBAT_D->do_damage(me, target, (flagremote ? REMOTE_ATTACK : UNARMED_ATTACK), damage, 135 + lvl_jingxin /25 + lvl_emjy / 20, 
                                                NOR CYN "$N" NOR CYN "大喝一声，双袖鼓荡起" + ((flagremote) ? BLINK : NOR) + HIW "峨眉九阳"  
                                                NOR CYN + ((flagremote) ? "螺旋透劲" : "劲气") + "，用力往前一推。\n" NOR
                                                HIR "只听轰然一声巨响，$n" HIR "被$N"
                                                HIR "一招正中，身子便如稻草般平平飞出"
                                                "，重\n重摔在地下，呕出一大口鲜血，动"
                                                "也不动。\n" NOR);
                                                        }
                }
                else
                                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 145 + lvl_jingxin /25, 
                                                HIR "只听轰然一声巨响，$n" HIR "被$N"
                                                HIR "一招正中，身子便如稻草般平平飞出"
                                                "，重\n重摔在地下，呕出一大口鲜血，动"
                                                "也不动。\n" NOR);
        } else
        {
                addn("neili", -500, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "内力深厚，及时摆脱了"
                       CYN "$P" CYN "内力的牵扯，躲开了这一击！\n" NOR;
        }
        message_combatd(msg, me, target);

                time = 20;
                time -= query("level", me) / 50;
                if (time < 15) time = 15;
                if ( BUFF_D->check_buff(me, "ljz-niepan") ) time -= 5;
                if( BUFF_D->check_buff(me, "ljz_fengyun") ) time /= 2;
                buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "emaq_piaoxuezhao",
                "attr"   : "curse",
                "name"   : "飘雪穿云掌·佛光普照",
                "time"   : time,
                "buff_msg" : "佛光普照消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
                ]);
                BUFF_D->buffup(buff);
        
        return 1;
}

