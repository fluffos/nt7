// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "刀至上-至上刀" NOR; }

int perform(object me)
{
        mapping buff;
        int dt;
        string msg;
        object weapon, target, weapon2;
        mixed res;
        int ap, dp, count;
        int i, damage;
        int time;
        int fmsk = me->query_skill("motun-tianxia", 1);
        int delta;

        /*
        if( query("family/family_name", me) != "魔教" &&
            query("reborn/family_name", me) != "魔教" )
                return notify_fail("你不是魔教弟子，无法使用" + name() + "。\n");
        */

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用" + name() + "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( me->is_busy() )
                return notify_fail("你正在忙着呢。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("moon-blade", 1) < 1000)
                return notify_fail("你圆月弯刀火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "moon-blade")
                return notify_fail("你没有激发圆月弯刀，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( userp(me) )
        {
                if( (dt = BUFF_D->get_buff_overtime(me, "yywd_dao")) > 0 )
                        return notify_fail(MAG"刀至上-至上刀消耗心神太甚，还需等待"+dt+"秒。\n"NOR);
        }

        ap = attack_power(me, "blade");
        ap += ap * (fmsk/100)* 5 / 100;
        dp = defense_power(target, "force");
        
        delta = ABILITY_D->check_ability(me, "ap_power-yywd-dao"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if( objectp(weapon2=query_temp("weapon", target)) )
        {
                msg = HBYEL "$N" HBYEL "双手持刀，一跃而起，劲运刀身，划出一道完美的弧线，一股刀劲"
                      HBYEL "如一轮新月袭向$n。\n" NOR;

                if (ap / 2 + random(ap) > dp)
                {
                        addn("neili", -500, me);
                        msg += HIR "$n" HIR "暗叫不好，连忙举起手中兵器抵挡，却不想虎口剧痛，手中" + weapon2->name() +
                               HIR "捏不住，脱手而出。\n" NOR;

                        weapon2->move(environment(me));
                } else
                {
                        addn("neili", -500, me);
                        msg += CYN "$n" CYN "提升十成功力，头上青筋暴出，紧握手中" + weapon2->name() +
                               CYN "硬是将$N" CYN "的劲气抵挡化解了。\n" NOR;
                }
                message_combatd(msg, me, target);
        }

        msg = HBBLU "霎时间$N" HBBLU "身法变得飘忽，不知何时已闪至$n的身前，一招" HIY "「刀至上」\n" NOR +
              HBBLU "刀尖由下至上划出一个形如满月的气劲飞向$n，誓要把$n一分两半" HBBLU "。\n"NOR;


        dp = defense_power(target, "dodge");
        damage = damage_power(me, "blade");
        
        delta = ABILITY_D->check_ability(me, "da_power-yywd-dao"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
        if (ap / 2 + random(ap * 2) > dp)
        {
                damage+= query("jiali", me);
                damage+= me->query_all_buff("damage");
                damage+= damage / 300 * me->query_str();
                damage += damage * (fmsk/100)* 5 / 100;
                damage*= 6;
                target->receive_damage("jing", damage / 8);
                target->receive_wound("jing", damage / 10);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200+fmsk/10,
                                              HIR "$n" HIR "只觉呼吸紧迫，一股劲风扑面"
                                             "而来，根本避无所避，被$N" HIR "的劲气袭中"
                                             "全身，各大穴道血气翻腾，血入箭般喷出。\n" NOR);
                target->set_weak(5);
                addn("neili", -400, me);
        } else
        {
                msg += CYN "$n" CYN "眼见$N" CYN "来势汹涌，丝毫不"
                       "敢小觑，急忙闪在了一旁。\n" NOR;
                addn("neili", -200, me);
        }

        message_combatd(msg, me, target);

        msg = HBMAG "紧跟着$N" HBMAG "跃向空中，另一杀招" HIB "「至上刀」" NOR +
                   HBMAG "手中刀狂舞，一瞬间天空中多出了无数个满月，一起向$n" HBMAG "飞去。\n" NOR;

        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "面对$N" HIR "这排山倒海般的攻"
                       "势，完全无法抵挡，招架散乱，连连退后。\n" NOR;
                count = ap / 5;
        } else
        {
                msg += HIC "$n" HIC "心底微微一惊，心知不妙，急忙"
                       "凝聚心神，竭尽所能化解$N" HIC "数道刀劲。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count*2, me);

        for (i = 0; i < 12; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy())
                        target->start_busy(3);

                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }
        addn("neili", -500, me);
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count*2, me);
        
        me->start_busy(2 + random(4));

        time = 40;
        time -= ABILITY_D->check_ability(me, "cd-yywd-dao"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
        if( wiz_level(me) > 2) time = 2;
        buff =
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "yywd_dao",
                "attr"   : "curse",
                "name"   : "圆月弯刀·刀至上-至上刀",
                "time"   : time,
                "buff_msg" : "刀至上-至上刀消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);
        return 1;
}

