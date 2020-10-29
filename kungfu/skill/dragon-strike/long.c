#include <ansi.h>
#include <combat.h>

#define HUI "「" HIR "龙嘯九天" NOR "」"
#define HUIP "「" HIR "亢龙有悔" HIW "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        int damage;
        string msg;
        int ap, dp, i;
        object weapon;
        int time;
        int delta;
        int fmsk = me->query_skill("bixue-danxin", 1);
        int ds = me->query_skill("dragon-strike", 1);
        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用" HUI "。\n");
        /*
        if( query("family/family_name", me) != "丐帮" 
        &&  member_array("丐帮", query("reborn/fams", me)) == -1 ) 
                return notify_fail("你尚未转世重生，无法使用" HUI "。\n");
        */
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能对战斗中的对手使用。\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(HUI "只能空手使用。\n");

        if ((int)me->query_skill("force", 1) < 1000)
                return notify_fail("你内功修为不够，难以施展" HUI "。\n");

        if( query("max_neili", me)<20000 )
                return notify_fail("你内力修为不够，难以施展" HUI "。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 1000)
                return notify_fail("你降龙十八掌火候不够，难以施展" HUI "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你没有激发降龙十八掌，难以施展" HUI "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你没有准备降龙十八掌，难以施展" HUI "。\n");

        if ((int)query("neili", me) < 10000)
                return notify_fail("你现在真气不够，难以施展" HUI "。\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "xlz_long")) > 0 )
                        return notify_fail(MAG"龙嘯九天消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        message_combatd(sort_msg(HIG "\n$N" HIG "凝神聚气，神态淡然，左手虚划，右手回转，聚气于胸前，猛地双"
                         "手推出，刹那间，一招变为数招，同时使出，正是降龙十八掌「" HIR "龙嘯九天" HIG "」，"
                         "气势恢弘，势不可挡 ……\n" NOR), me, target);

        // 第一掌
        ap = attack_power(me, "strike") + me->query_str() * 15;
        dp = defense_power(target, "dodge") + target->query_dex() * 15;
        ap *= 2;
        delta = ABILITY_D->check_ability(me, "ap_power-xlz-long"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        message_combatd(sort_msg(HIW "忽然$N" HIW "身形激进，左手一划，右手呼的一掌"
                     "拍向$n" HIW "，力自掌生之际"
                     "说到便到，以排山倒海之势向$n" HIW "狂涌而去，当真石"
                     "破天惊，威力无比。\n" NOR), me, target);

        damage = damage_power(me, "strike");
                damage+= me->query_all_buff("unarmed_damage");
        damage+= query("jiali", me) * 5;
                damage+= damage / 300 * me->query_str();
                damage/= 18;
                damage = damage + damage /10 * query("str",me);
                damage = damage + damage / 500 * fmsk;
        if(query("shen",me) > query("combat_exp",me))
                   damage*= 2;
                if(me->query_skill("yijin-duangu",1) > ds-200)
                {
                   damage*= 2;
                }
        if( target->query_family() == "星宿派" || target->query_family() == "逍遥派" )
            damage *= 3;
                
        delta = ABILITY_D->check_ability(me, "da_power-xlz-long"); // 门派ab
        if( delta ) damage += damage*delta/100;
        if (ap * 3 / 5 + random(ap) + fmsk > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200 + fmsk / 5,
                                          HIR "$P身形一闪，竟已晃至$p跟前，$p躲"
                                          "闪不及，顿被击个正中。\n" NOR);
        } else
        {
                msg = HIC "却见$p气贯双臂，凝神应对，$P掌"
                      "力如泥牛入海，尽数卸去。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第二掌
        damage += damage / 3;
        ap = attack_power(me, "strike") + me->query_str() * 15;
        dp = defense_power(target, "parry") + target->query_int() * 15;
        ap *= 2;
        delta = ABILITY_D->check_ability(me, "ap_power-xlz-long"); // 门派ab
        if( delta ) ap += ap*delta/100;
        message_combatd(sort_msg(HIW "$N" HIW "一掌既出，身子已然抢到离$n" HIW "三"
                     "四丈之外，后掌推前掌两股掌力道合并，掌力犹如怒潮狂"
                     "涌，势不可当。霎时$p便觉气息窒"
                     "滞，立足不稳。\n" NOR), me, target);

        if (ap /2 + random(ap) + fmsk > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 250 + fmsk / 5,
                                          HIR "$p一声惨嚎，被$P这一掌击中胸前，"
                                          "喀嚓喀嚓断了几根肋骨。\n" NOR);
        } else
        {
                msg = HIC "可是$p全力抵挡招架，竟似游刃有"
                      "余，将$P的掌力卸于无形。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第三掌
        damage += damage / 2;
        ap = attack_power(me, "strike") + me->query_str() * 15 + me->query_skill("force");
        dp = defense_power(target, "force") + target->query_con() * 15;
        ap *= 2;
        delta = ABILITY_D->check_ability(me, "ap_power-xlz-long"); // 门派ab
        if( delta ) ap += ap*delta/100;
        message_combatd(sort_msg(HIW "紧跟着$N" HIW "右掌斜挥，前招掌力未消，此招掌"
                     "力又到，竟然又攻出一招，掌夹风势，势如破竹，"
                     "便如一堵无形气墙，向前疾冲而去。$n" HIW "只觉气血翻"
                     "涌，气息沉浊。\n" NOR), me, target);

        if (ap /2 + random(ap) + fmsk > dp)
        {
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + fmsk / 5,
                                          HIR "结果$p躲闪不及，$P掌劲顿时穿胸而"
                                          "过，顿时口中鲜血狂喷。\n" NOR);
        } else
        {
                msg = HIC "$p眼见来势凶猛，身形疾退，瞬间"
                      "飘出三丈，脱出掌力之外。\n" NOR;
        }
        message_combatd(msg, me, target);

        message_combatd(sort_msg(HIY "$N" HIY "毫无停顿，双掌翻滚，宛如一条神龙攀蜒于九天之上"
                        "。\n" NOR), me, target);

        addn_temp("apply/attack", ds*2+fmsk*5, me);
        addn_temp("apply/unarmed_damage", ds*2+fmsk*5, me);
        for (i = 0; i < 6; i++)
        {
                if (!me->is_fighting(target)||!living(target))
                        break;

                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                                                
                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }
        addn_temp("apply/attack", -ds*2-fmsk*5, me);
        addn_temp("apply/unarmed_damage", -ds*2-fmsk*5, me);

        weapon=query_temp("weapon", target);
        if (objectp(weapon))
        {
                message_combatd(sort_msg(HIG "\n$N" HIG "暴喝一声，全身内劲迸发，气贯右臂奋力外扯，企图将$n"
                                HIW "的" + weapon->name() + HIW "吸入掌中。\n" NOR), me, target);

                ap = attack_power(me, "strike") + me->query_str() * 20;
                dp = defense_power(target, "parry") + target->query_dex() * 20;
                ap = ap + ap / 2;
                if (!playerp(target)) ap *= 7 / 2;

                if (ap / 3 + random(ap) > dp)
                {
                        addn("neili", -500, me);
                        msg = HIR "$n" HIR "只觉周围气流涌动，手中" + weapon->name()
                               + HIR "竟然拿捏不住，向$N" HIR "掌心脱手飞去。\n" NOR;
                        weapon->move(me, 1);
                } else
                {
                        addn("neili", -250, me);
                        msg = CYN "$n" CYN "只觉周围气流涌动，慌忙中连将手中"
                               + weapon->name() + CYN "挥舞得密不透风，使得$N"
                               CYN "无从下手。\n" NOR;
                }
                message_combatd(msg, me, target);
        }

        if (random(5) == 1)
        {
                message_combatd(HIG "$N" HIG "生平从未见过如此凌厉恢弘的招式，竟被弄得不知所措。\n" NOR,
                                target);
                if( !target->is_busy() )
                        target->start_busy(5 + random(6));
        }

        me->start_busy(3 + random(3));
        addn("neili", -5000, me);
        
        time  = 38;
        //time -= ABILITY_D->check_ability(me, "cd-xlz-long"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "cd-xlsbz-long"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd 
        if(wizardp(me) && query("id",me)=="mud") time = 2;       
        buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "xlz_long",
                "attr"   : "curse",
                "name"   : "降龙十八掌·龙嘯九天",
                "time"   : time,
                "buff_msg" : "龙嘯九天消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        
        BUFF_D->buffup(buff);
        return 1;
}




