#include <ansi.h>
#include <combat.h>

string name() { return HIR "灵犀一指" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int ap, dp, damage, p;
        int fmsk = me->query_skill("qimen-xuanshu", 1);
        int delta, delta2;
        int time;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail(name() + "只能对战斗中的对手使用。\n");
                                
        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用" + name() + "。\n");
                                
        if( (int)me->query_skill("tanzhi-shentong", 1) < 100 )
                return notify_fail("你的弹指神通不够娴熟，无法使用灵犀一指。\n");

        if( query_temp("weapon", me) )
                return notify_fail("灵犀一指须空手使用。\n");

        if( (int)me->query_skill("tanzhi-shentong", 1) < 1000 )
                return notify_fail("你的弹指神通不够娴熟，难以施展" + name() + "。\n");

        if( (int)me->query_skill("qimen-wuxing", 1) < 200 )
                return notify_fail("你的奇门五行修为不够，难以施展" + name() + "。\n");
                
        if( me->query_skill_mapped("finger") != "tanzhi-shentong" )
                return notify_fail("你没有激发弹指神通，难以施展" + name() + "。\n");

        if( me->query_skill_prepared("finger") != "tanzhi-shentong" )
                return notify_fail("你没有准备弹指神通，难以施展" + name() + "。\n");

        if( query("neili", me) < 3500 )
                return notify_fail("你的内力不足，难以施展" + name() + "。\n");

        if( !living(target) )
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "tzst_lingxi")) > 0 )
                        return notify_fail(MAG"灵犀一指消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        msg = HIR "只见$N" HIR "周身罡气激荡，浑身上下一片绯红，像是变成了火焰晶体，整个人燃烧起来。浑身火焰如一条条江河一般，朝着$N"HIR"食指指尖涌去。\n"NOR;
        msg += HIY "一刹那，指尖的火焰光芒耀眼无比，将天上的阳光都完全遮挡了下来，整个天地突然就暗了下来，唯有那一点光芒，夺目刺眼。\n" NOR;
        msg += HIW "那一点光芒在$n"HIW"眼中已化作千道，万道，空间裂开一道道细缝，而$N"HIW"的身影却慢慢高大起来，潮声渐落，那一点光芒久久不见消散。\n";
        target->set_weak(5);
        if( !target->is_busy() ) target->start_busy(2);
        
        ap = attack_power(me, "finger") + me->query_skill("qimen-wuxing", 1);
        dp = defense_power(target, "dodge") + target->query_skill("qimen-wuxing", 1);
        
        delta = ABILITY_D->check_ability(me, "ap_power-tzst-lingxi"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        damage = damage_power(me, "finger");
        damage+= query("jiali", me);
        damage+= me->query_all_buff("unarmed_damage");
        damage+= damage / 300 * me->query_str();
        damage*= 6;
           
        delta2 = ABILITY_D->check_ability(me, "da_power-tzst-lingxi"); // 门派ab
        if( delta2 ) damage += damage*delta2/100;

        ap *= 2;
        if( ap / 2 + random(ap) > dp ) 
        {
                msg += "$n躲闪不及，“噗”地一声，被指劲击中前胸！\n";
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 375 + fmsk / 10, 
                                                   HIR "你听到“嗤”的一声，身上竟然溅到几滴鲜血！\n" NOR);
        } 
        else if( ap / 2 + random(ap) + fmsk > dp ) 
        {
                msg += "$n向旁边一闪，让过了劲风，没想到这股指劲竟然有回力，从$n背后倒转回来，正刺中$p的后背。\n";
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 375 + fmsk / 20, 
                                                   HIR "你听到“嗤”的一声，身上竟然溅到几滴鲜血！\n" NOR);
                
        }
        else
        {
                msg += "$n向旁边一闪，让过了劲风，却忽然发觉这股指劲竟然有回力，匆忙中只好一个前扑才堪堪躲过，模样狼狈之极。\n" NOR;
        }
        message_combatd(msg, me, target); 
        me->add("neili", -3000);
        me->start_busy(3);

        time = 40;
        time -= ABILITY_D->check_ability(me, "cd-tzst-lingxi"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd  
        if( wiz_level(me) > 2) time = 2;                
        buff =  
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "tzst_lingxi",
                "attr"   : "curse",
                "name"   : "弹指神通·灵犀一指",
                "time"   : time,
                "buff_msg" : "灵犀一指消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);
        return 1;
}


