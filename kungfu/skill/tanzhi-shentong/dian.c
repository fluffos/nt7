// dian.c
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string name() { return HIR "隔" HIY "空" HIG "点" HIW "穴" NOR; }
int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int ap, dp, jp, lvl, xw, j, damage;
        int delta, delta2;
        int time;
        
        if (! target) target = offensive_target(me);

        if( query_temp("weapon", me) )
                return notify_fail("你拿着武器怎么能准确的点中对方的穴道呢！\n");

        if (!target || ! me->is_fighting(target))
             return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if((int)me->query_skill("dodge",1) < 200)
                return notify_fail("你的轻功修为不够, 不能使用隔空点穴！\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你没有激发弹指神通，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你没有准备弹指神通，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if((int)me->query_skill("tanzhi-shentong",1) < 200)
                return notify_fail("你的弹指神通修为不够， 目前不能使用隔空点穴! \n");

        if( query("neili", me)<5000 )
                return notify_fail("你的真气不够！\n");

        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "tzst_dian")) > 0 )
                        return notify_fail(MAG"隔空点穴消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }

        //lvl = me->query_skill("tanzhi-shentong",1);
        lvl = me->query_skill("force");
        jp = me->query_skill("jingluo-xue", 1)*10;

        //随机产生点中的穴位
        xw = (int)random(15);
        if (xw > 8)
        {
                xw = random(8);
        }

        msg = HIY "\n陡见$N" HIY "耐心的绕着$n旋走，突然只听见$N大喊一声:看我桃花" NOR+name()+HIY"，着 !\n" NOR;
        message_combatd(msg, me, target);
        damage = damage_power(me, "finger");
        damage+= query("jiali", me);
        damage*= query("str",me);
        
        delta2 = ABILITY_D->check_ability(me, "da_power-tzst-dian"); // 门派ab
        if( delta2 ) ap += ap*delta2/100;
                                
        // 伏兔穴
        //if (xw == 1)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("dodge");
                dp = defense_power(target, "parry") + target->query_skill("dodge");
                
                delta = ABILITY_D->check_ability(me, "ap_power-tzst-dian"); // 门派ab
                if( delta ) ap += ap*delta/100;
        
                msg = HIG "\n$n聚气於右手食指，倏地向$N腿上伏兔穴点去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$N赶紧缩脚，才闪过这一招。\n" NOR;
                else
                {
                        msg += HIR "$N一被点中，腿一麻，身法登时迟缓了下来。\n" NOR;
                        //set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        data = ([
                                "dodge": -lvl,
                        ]);
                        buff = ([
                                "caster" : me,
                                "target" : target,
                                "type"   : "tanzhi_dian1",
                                "attr"   : "curse",
                                "name"   : "弹指神通·伏兔穴",
                                "time"   : 30,
                                "buff_msg" : msg,
                                "disa_msg" : HIY"$N腿上的伏兔穴血脉已经行开，身法已复。\n" NOR,
                                "disa_type": 1,
                        ]);
                        BUFF_D->buffup(buff);        
                        
                }
//                message_combatd(msg, me, target);
        }

// 神门穴
        //else if (xw == 2)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                
                if( delta ) ap += ap*delta/100;
                
                msg = HIG "\n$n聚气於右手食指，倏地向$N手腕神门穴点去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$N赶紧翻转手腕，才避开了这一招。\n" NOR;
                else
                {
                        msg += HIR "$N一被点中，手腕一麻，力道弱了许多。\n" NOR;
                        //set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        data = ([
                                "attack": -lvl,
                        ]);
                        buff = ([
                                "caster" : me,
                                "target" : target,
                                "type"   : "tanzhi_dian2",
                                "attr"   : "curse",
                                "name"   : "弹指神通·神门穴",
                                "time"   : 30,
                                "buff_msg" : msg,
                                "disa_msg" : HIY"$N腿上的神门穴血脉已经行开，力道已复。\n" NOR,
                                "disa_type": 1,
                        ]);
                        BUFF_D->buffup(buff); 
                }
//                message_combatd(msg, me, target);
        }

// 关元穴
        //else if (xw == 3)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("force");
                dp = defense_power(target, "parry") + target->query_skill("force");
                
                if( delta ) ap += ap*delta/100;
                
                msg = HIG "\n$N聚气於右手食指，倏地向$n腹部关元穴点去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n赶紧退了一步，才闪了过去。\n" NOR;
                else
                {
                        msg += HIR "$n一被点中，一股热气直冲丹田，体内的真气被打散了开去！\n" NOR;
                        //set_temp("thd/tz", 1, me);
                        set("neili", 0, target);
                        addn("neili", -150, me);
                }
                message_combatd(msg, me, target);
        }
         // 玉堂穴
        //else if (xw == 4)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("bibo-shengong", 1);
                dp = defense_power(target, "dodge") + target->query_skill("force", 1);
                
                if( delta ) ap += ap*delta/100;
                
                msg = HIG "\n$n聚气於右手食指，倏地向$N胸口玉堂穴点去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$N急忙抽过武器抵挡袭的指气，一边急忙抽身回撤，"
                                   "方躲过这一招。\n" NOR;
                else
                {
                        msg += HIR "$N一被点中，体内的真气再也不能运转自如，招架顿时散乱。\n" NOR;
                        //set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        j = me->query_skill("bibo-shengong",1);
                        data = ([
                                "parry": -j,
                        ]);
                        buff = ([
                                "caster" : me,
                                "target" : target,
                                "type"   : "tanzhi_dian4",
                                "attr"   : "curse",
                                "name"   : "弹指神通·神门穴",
                                "time"   : 30,
                                "buff_msg" : msg,
                                "disa_msg" : HIY "$N胸口的玉堂穴血脉已经行开，内息恢复了正常。\n" NOR,
                                "disa_type": 1,
                        ]);
                        BUFF_D->buffup(buff); 

                        //target->apply_condition("no_exert", j);
                }
 //               message_combatd(msg, me, target);
        }

// 檀中穴
        //else if (xw == 5)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("dodge");
                dp = defense_power(target, "parry") + target->query_skill("dodge");
                
                if( delta ) ap += ap*delta/100;
                
                msg = HIG "\n$N聚气於右手食指，倏地向$n胸前檀中穴点去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n连退两步，才闪过这一招。\n" NOR;
                else
                {
                        msg += HIR "$n一被点中，气息一窒，一时难以动弹。\n" NOR;
                        //set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        if (!target->is_busy())
                                target->start_busy(ap /90 + 2);
                }
                message_combatd(msg, me, target);
        }

// 灵台穴
        //else if (xw == 6)
        {
                ap = attack_power(me, "finger") + jp+query("max_neili", me);
                dp = defense_power(target, "dodge")+query("max_neili", target);
                
                if( delta ) ap += ap*delta/100;
                
                msg = HIG "\n$N聚气於右手食指，倏地向$n背後灵台穴点去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n急忙运气内力，强行以内力顶住对方的指气。\n" NOR;
                else
                {
                        msg += HIR "$n一被点中，脸上时红时白，看来受了内伤。\n" NOR;
                        //set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        target->receive_damage("jing", damage );
                        target->receive_wound("jing", damage / 2 );
                }
                message_combatd(msg, me, target);
        }

// 百会穴
        //else if (xw == 7)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                
                if( delta ) ap += ap*delta/100;
                
                msg = HIG "\n$N聚气於右手食指，倏地向$n头部百会穴点去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n一仰头，才躲过这一招。\n" NOR;
                else
                {
                        msg += HIR "$n一被点中，登时天悬地转，摇摇遇坠。\n" NOR;
                        //set_temp("thd/tz", 1, me);
                        target->receive_damage("qi", damage);
                        target->receive_wound("qi", damage/2);
                        addn("neili", -150, me);
                }
                message_combatd(msg, me, target);
        }

// 风府穴
        //else if (xw == 8)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                
                if( delta ) ap += ap*delta/100;
                
                msg = HIG "\n$n聚气於右手食指，倏地向$N後脑风府穴点去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$N赶紧低头，才闪过这一招。\n" NOR;
                else
                {
                        msg += HIR "$N一被点中，眼前陡然一黑，几乎昏倒。\n" NOR;
                        //set_temp("thd/tz", 1, me);
                        
                        addn("neili", -150, me);
                        data = ([
                                "defense": -lvl,
                        ]);
                        buff = ([
                                "caster" : me,
                                "target" : target,
                                "type"   : "tanzhi_dian8",
                                "attr"   : "curse",
                                "name"   : "弹指神通·风府穴",
                                "time"   : 30,
                                "buff_msg" : msg,
                                "disa_msg" : HIY "$N胸口的风府穴血脉已经行开，视线复原了。\n" NOR,
                                "disa_type": 1,
                        ]);
                        BUFF_D->buffup(buff); 
                }
//                message_combatd(msg, me, target);
        }
// 未对应
        //else return notify_fail("你运用弹指神通乱点一通，看样子是毫无作用。\n");

        me->start_busy(3);
        return 1;
}

