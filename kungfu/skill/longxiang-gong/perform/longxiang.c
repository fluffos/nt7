// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "十龙十象" NOR; }

inherit F_SSERVER;

string final1(object me, object target, int damage, object weapon, int lvl);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage, object weapon, int lvl);
string final4(object me, object target, int ap);
void tian_end(object me, object target);

int perform(object me, object target)
{
        mapping buff, data;
        int damage;
        string msg;
        int ap, dp;
        int lvl;
        int time;
        int delta, delta2;
        int fmsk = me->query_skill("mizong-zhenyan", 1);
        
        if( userp(me) && !query("yuanshen", me) ) 
                return notify_fail("你尚未悟道，所使用的外功中没有这个功能。\n"); 

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能对战斗中的对手使用。\n");
        
        if( me->is_busy() )
                return notify_fail("你正忙着呢！\n");
                
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) ) 
                return notify_fail(name() + "只能空手使用。\n"); 

        if ((int)me->query_skill("force", 1) < 1000)
                return notify_fail("你内功修为不够，难以施展" +name()+ "。\n");

        if( query("max_neili", me)<100000 )
                return notify_fail("你内力修为不够，难以施展" +name()+ "。\n");

        lvl = (int)me->query_skill("longxiang-gong", 1);
        if (lvl < 1000)
                return notify_fail("你龙象般若功火候不够，难以施展" +name()+ "。\n");

        if( query("neili", me)<10000 )
                return notify_fail("你现在真气不够，难以施展" +name()+ "。\n");

        if (me->query_skill("martial-cognize", 1) < 400)
                return notify_fail("你武学修养不足，难以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "lxg_longxiang")) > 0 )
                        return notify_fail(MAG"十龙十象消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        message_combatd(HIM "\n$N" HIM "运起十龙十象之力，霎时金波流转，罡气笼罩全身，\n"
                        HIM "$N" HIM "纵声长啸，漫天掌力狂涌而去，当真石破天惊，威力无比，袭向$n" HIM "。\n" NOR, me, target);

        message_combatd(HIM "十龙十象之一龙一象\n" NOR, me, target);
        
        me->addn("neili", -10000);
        
        // 第一招，判断对方臂力
        ap = attack_power(me, "unarmed") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_str()*10;
        
        delta = ABILITY_D->check_ability(me, "ap_power-lxg-longxiang"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        damage = damage_power(me, "unarmed");
        damage += query("jiali", me);
        damage *= 3;
        
        delta2 = ABILITY_D->check_ability(me, "da_power-lxg-longxiang"); // 门派ab
        if( delta2 ) damage += damage*delta2/100;
        
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + fmsk/10,
                                         (: final1, me, target, damage, lvl :));
        } else
        {
                msg = HIC "$n" HIC "气贯双臂，凝神以对，竟将$N" HIC "之力卸去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之二龙二象\n" NOR, me, target);
        
        ap = attack_power(me, "unarmed") + me->query_int()*10;
        // 第二招，判断对方悟性
        dp=defense_power(target,"parry")+target->query_int()*10;
        
        if( delta ) ap += ap*delta/100;
        
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + fmsk/10,
                                          HIY "$n" HIY "冷笑一声，觉得$N" HIY "此招肤浅之极，于"
                                          "是随意招架，猛然间，「噗嗤」！一声，双掌"
                                          HIY "已穿透$n" HIY "的胸膛，鲜血不断涌出。\n" NOR, me , target);
        } else
        {
                msg = HIC "$n" HIC "会心一笑，看出$N" HIC "这招中的破绽，随意施招竟将这招化去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之三龙三象\n" NOR, me, target);
        
        ap = attack_power(me, "unarmed") + me->query_con()*10;
        // 第三招，判断对方根骨
        dp = defense_power(target, "force") + target->query_con()*10;
        
        if( delta ) ap += ap*delta/100;
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + fmsk/10,
                                           (: final2, me, target, damage :));
        } else
        {
                msg = HIC "$n" HIC "默运内功，内劲贯于全身，奋力抵挡住$N" HIC "这招。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之四龙四象\n" NOR, me, target);

        // 第四招，判断对方身法

        ap = attack_power(me, "unarmed") + me->query_dex()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;
        
        if( delta ) ap += ap*delta/100;
        
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + fmsk/10,
                                          (: final3, me, target, damage, lvl :));
        } else
        {
                msg = HIC "$n" HIC "见这招来势凶猛，身形疾退，瞬间飘出三"
                      "丈，方才躲过$N" HIC "这招。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之五龙五象\n" NOR, me, target);

        // 第五招，判断对方内力

        if( query("max_neili", me)>query("max_neili", target)*2 )
        {
                 msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + fmsk/10,
                        HIY "$n" HIY "思虑未定，$N" HIY "的内劲已破体而入，"
                            "$n" HIY "受此重击，喉口一甜，呕出数口" HIR "鲜血" HIY "。\n" NOR, me, target);
        } else
        {
                msg = CYN "$n" CYN "知道$N这招无可抵挡，"
                       CYN "当即飞身跃起丈许，躲闪开来。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之六龙六象\n" NOR, me, target);

        // 第六招，判断对方江湖阅历

        if( query("score", me)>query("score", target)*2 )
        {
                 msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80 + fmsk/10,
                                          (: final4, me, target, damage :));
        } else
        {
                msg = CYN "$n" CYN "会心一笑，一招击在气墙中心，竟将此招破去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之七龙七象\n" NOR, me, target);
        
        // 第七招，判断对方基本内功
        
        ap = attack_power(me, "unarmed") + me->query_skill("force", 1);
        dp = defense_power(target, "parry") + target->query_skill("force", 1);
        
        if( delta ) ap += ap*delta/100;
        
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + fmsk/10,
                        HIY "$n" HIY "思虑未定，$N" HIY "的内劲已破体而入，"
                            "$n" HIY "受此重击，喉口一甜，呕出数口" HIR "鲜血" HIY "。\n" NOR, me, target);
        } else
        {
                msg = CYN "$n" CYN "面对$N" CYN "这排山倒海攻势，完全"
                                          CYN "无法抵挡，唯有退后几步，凝神应对。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之八龙八象\n" NOR, me, target);
        
        // 第八招，判断对方基本招架
        
        ap = attack_power(me, "unarmed") + me->query_skill("parry", 1);
        dp = defense_power(target, "parry") + target->query_skill("parry", 1);
        
        if( delta ) ap += ap*delta/100;
        
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + fmsk/10,
                        HIY "$n" HIY "腾挪闪躲，竭尽全力，也没办法躲开气旋，被击了个正着！\n" NOR, me, target);
        } else
        {
                msg = HIC "$n" HIC "见这招来势凶猛，身形疾退，瞬间飘出三"
                      "丈，方才躲过$N" HIC "这招。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之九龙九象\n" NOR, me, target);
        
        // 第九招，判断对方基本轻功
        
        ap = attack_power(me, "unarmed") + me->query_skill("dodge", 1);
        dp = defense_power(target, "parry") + target->query_skill("dodge", 1);
        
        if( delta ) ap += ap*delta/100;
        
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + fmsk/10,
                                          HIY "$n犹如和数十人战斗，哪里还能抵挡的住，"
                                          HIY "仅仅数息之间，已经身中数招！\n" NOR, me , target);
        } else
        {
               msg = CYN "$n大吃一惊，连忙退后，居然"
                      CYN "侥幸躲开了这一招！\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "十龙十象之十龙十象\n" NOR, me, target);
        
        // 第十招，判断对方武学修养
        
        ap = attack_power(me, "unarmed") + me->query_skill("martial-cognize", 1);
        dp = defense_power(target, "parry") + target->query_skill("martial-cognize", 1);
        
        if( delta ) ap += ap*delta/100;
        
        damage *= 3;
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 300 + fmsk/10,
                        HIY "$n" HIY "面对威力如此强大的一招，根本无法招架，被重重击中，\n"
                        HIY "五脏六腑翻腾不休，口中" HIR "鲜血" HIY "如箭般喷出！\n" NOR, me, target);
        } else
        {
                msg = CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        
        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-lxbrg-longxiang"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
                
        buff =  
	([
	        "caster" : me,
	        "target" : me,
	        "type"   : "cooldown",
	        "type2"  : "lxg_longxiang",
	        "attr"   : "curse",
	        "name"   : "龙象般若功·十龙十象",
	        "time"   : time,
	        "buff_msg" : "十龙十象消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
	        "disa_msg" : "",
	        "disa_type": 0,
	]);
	BUFF_D->buffup(buff);
        me->start_busy(6 + random(5));
        if( BUFF_D->get_buff_overtime(me, "longxiang10") > 0 ) return 1;
        buff =  
	([
	        "caster" : me,
	        "target" : me,
           "type"   : "protectshield",
           "type2":"longxiang10", 
           "attr":"bless", 
           "name"   : "龙象般若功·十龙十象之力",
           "time"   : lvl/10,
           "buff_msg" : HIB"$n身边霎时金波流转，十龙十象之力笼罩全身。\n"NOR, 
	        "disa_msg" : "",
	        "disa_type": 0,
         "shield_type":"neili", 
         "shield_amount":lvl*10000,
         "shield_desc":HIB"$n身边霎时金波流转，十龙十象之力笼罩全身，将$N攻击阻在其外。\n"NOR, 
	]);
	BUFF_D->buffup(buff);
	     
        return 1;
}

string final1(object me, object target, int damage, int lvl)
{
        addn("neili", -(lvl+random(lvl)), target);

        return  HIY "$n" HIY "却觉$N" HIY "这招气势恢弘，于是运力奋力抵挡。但是无奈这"
                "招威力惊人，$n" HIY "闷哼一声，倒退几步，顿觉内息涣散，身"
                "上早已染满鲜血！\n" NOR;
}

string final2(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);
        return  HIY "$n" HIY "心中一惊，但见$N" HIY "这几招奇异无比，招式变化莫测，"
                "但威力却依然不减，正犹豫间，$n" HIY "却已中招，顿感精力不济，浑"
                "身无力。\n" NOR;
}

string final3(object me, object target, int damage, int lvl)
{
   
        target->start_busy(4 + random(3));
  
        return  HIY "$N" HIY "掌法奇妙无比，双手时而宛若游龙，时而"
                "宛若惊鸿，霎那间$n" HIY "已遍体鳞伤，$N" HIY "猛然将双拳一"
                "转，拳势陡然加快，将$n" HIY "团团围住，竟无一丝空隙！\n" NOR;

}

void tian_end(object me, object target)
{
        if( target && query_temp("no_perform", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }
                addn_temp("apply/avoid_busy", 90, target);
                addn_temp("apply/reduce_busy", 36, target);
                addn_temp("apply/avoid_weak", 90, target);
                addn_temp("apply/avoid_forget", 90, target);
                tell_object(target, HIR "你的忽视虚弱，忽视忙乱、忽视绝招冷冻能力终于解除封印。\n" NOR);
                delete_temp("no_perform", target);
        }
        return;
}

string final4(object me, object target, int ap)
{
        mapping buff, data;
        string msg;
        
        msg = HIY "$n" HIY "丝毫不懂此招奥妙，一个疏神，丹田已遭重创！\n" NOR +
              WHT "$n" WHT "感到自身的忽视虚弱，忽视忙乱、忽视绝招冷冻能力被封印。\n" NOR;
               
        if( BUFF_D->check_buff(target, "longxiang_fengyin") ) 
                return msg;
                
        data = ([
                "avoid_busy": -90,
                "reduce_busy": -36,
                "avoid_weak": -90, 
                "avoid_forget": -90, 
        ]);
        buff = ([
                "caster": me,
                "target": target,
                "type"  : "longxiang_fengyin",
                "attr"  : "curse",
                "name"  : "龙象般若功·十龙十象",
                "time"  : 10+random(ap/50),
                "buff_data": data,      
                "buff_msg" : "",
                "disa_msg" : HIR "你的忽视虚弱，忽视忙乱、忽视绝招冷冻能力终于解除封印。\n" NOR,
                        
        ]);
        BUFF_D->buffup(buff);
        //set_temp("no_perform", 1, target);
        
        return msg;
}
