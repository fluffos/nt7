// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY"八荒独尊掌"NOR; }

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int ap, dp;
        int damage;
        int lvl,bhg,fmsk,flagremote;
        int delta, delta2;
        int time;

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你还没有悟道，还不能领悟到"+name()+"的精髓。\n");
        
        if( query("family/family_name", me) != "灵鹫宫" )
                return notify_fail("灵鹫宫的大招且是你能领会的？\n");
                
        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");

        if( !target )
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name()+"只能空手才能施展。\n");

        if( !me->is_fighting(target) )
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( !target || !target->is_character() )
                return notify_fail("你要对谁施展"+name()+"？\n");

        if( !living(target) )
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( me->query_skill_prepared("strike") != "liuyang-zhang" )
                return notify_fail("你还没有将天山六阳掌与逍遥折梅手互备，无法施展"+name()+"。\n");

        if( (int)me->query_skill("force") < 1000 )
                return notify_fail("你内功修为不够，难以施展" + name() + "。\n");

        if( lvl = me->query_skill("liuyang-zhang", 1) < 1000 )
                return notify_fail("你的天山六阳掌火候不够，无法施展"+name()+"。\n");

        if( query("neili", me) < 2500 )
                return notify_fail("你的真气不够，现在无法施展"+name()+"。\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "lyz_zun")) > 0 )
                        return notify_fail(MAG"八荒独尊掌消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        bhg = me->query_skill("bahuang-gong", 1);
                fmsk = me->query_skill("fanlao-huantong", 1);
                if( bhg>6000 && fmsk >1000 ) flagremote = SPECIAL_ATTACK;
                if( bhg>12000 && fmsk >2000 ) flagremote = REMOTE_ATTACK;
                
        msg = HIY "但见$N" HIY "衣袂飘飘翩跹起舞，闭目凝神默运玄功，手中生死符由内劲雾化蒸腾，\n"
              HIY "如云霞般随着双掌的翻飞缭绕周身，忽然$N" HIY "倾步前移，双掌破空击出，挟着丝丝寒意，直向$n" HIY "双肩贯去。\n" NOR;

        msg += HIR "$n" HIR "只觉胸口一闷，一丝凉意直入肺腑，脑中一片空白茫然不知所措！\n" NOR;

        target->affect_by("ss_poison",
                          ([ "level" : lvl * 200,
                             "id"    : query("id", me),
                             // "remain"   : -1,
                             "duration" : lvl / 100 + random(lvl / 10) ,
                          ]));
        // 第一掌
        ap = attack_power(me, "strike") + me->query_str()*20;
        dp = defense_power(target, "dodge") + target->query_str()*20;
        
        delta = ABILITY_D->check_ability(me, "ap_power-lyz-zun"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);
        damage+= me->query_all_buff("unarmed_damage");
        damage+= damage / 300 * me->query_str();
        damage = damage / 10 * 59;   
        
        delta2 = ABILITY_D->check_ability(me, "da_power-lyz-zun"); // 门派ab
        if( delta2 ) damage += damage*delta2/100;
                
        addn_temp("apply/add_damage", 100, me);
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, flagremote, damage, 200+fmsk/10,
                                           HIR "$n" HIR "恍然惊醒，心下大骇，慌乱中抬手相抗，怎料得$N"
                                           HIR "那凝脂如雪的双掌竟然蕴含千钧力道，\n"
                                           HIR "一触之下顿让自己双臂气劲溃散，毫无抵挡之力，结结实实地受下此招。\n" NOR);

        } else
        {
                msg += CYN "$p" CYN "眼见$P" CYN "来势汹涌，情急之下力贯双臂，奋起抵抗，居然未占下风。\n" NOR;
        }
        addn_temp("apply/add_damage", -100, me);
        message_combatd(msg, me, target);

        msg = HIY "$N" HIY "一招未老，瞬即抽身回翔，接着反手推出一掌，看似漫无目的，那汇聚着白虹掌力的内劲确如浪涌一般奔至$n"HIY"胸前。\n" NOR;
        // 第二掌
        ap = attack_power(me, "strike") + me->query_con()*20;
        dp = defense_power(target, "parry") + target->query_con()*20;
        
        if( delta ) ap += ap*delta/100;
        
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                target->set_weak(5);
                msg += COMBAT_D->do_damage(me, target, flagremote, damage, 300+fmsk/10,
                                           HIR "那掌劲不疾不徐，却又避无可避，从$n" HIR "胸口透体而过,直震得$n筋骨寸裂。\n"
                                           HIR "$n" HIR "只觉心脉如千道银针扎入，气海一阵翻涌，一团血雾从口中喷激而出。\n" NOR);

        } else
        {
                msg += CYN "只见$p" CYN "早有准备，猛一提气，内力从丹田源源不断灌入胸腔护住心脉，硬吃下这掌，倒也无甚大碍。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第三掌
        msg = HIY "$N" HIY "纵身一跃，蓦然腾空数丈，随着一声娇叱，已俯身飘摇而下，重重掌影层叠成一朵巨大的雪莲，朝$n" HIY "头顶压下。\n" NOR;

        ap = attack_power(me, "strike") + me->query_dex()*20;
        dp = defense_power(target, "force") + target->query_dex()*20;
        
        if( delta ) ap += ap*delta/100;
        
        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(5);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, flagremote, 400+fmsk/10,
                                           HIR "只听的一声闷响，一道雄浑的掌劲已在$n" HIR "天灵炸开，顺势泄入$n" HIR "周身，\n"
                                           HIR "$n" HIR "颅内一阵裂痛，全身经脉如浸寒冰，一下子瘫倒在地，动弹不得。\n" NOR);

        } else
        {
                msg += CYN "$p" CYN "见此招来势汹涌，岂敢贸然招架。俯腰移步，一个灵动，居然在千钧一发之际抽身而出。\n" NOR;
        }
        
        time  = 38;
        time -= ABILITY_D->check_ability(me, "cd-lyz-zun"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
                
        buff =  
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "lyz_zun",
                "attr"   : "curse",
                "name"   : "六阳掌·八荒独尊掌",
                "time"   : time,
                "buff_msg" : "八荒独尊掌消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);
        
        addn("neili", -1500, me);
        me->start_busy(2+random(2));
        message_combatd(msg, me, target);
        return 1;
}

