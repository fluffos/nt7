
// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "先天罡气" NOR; }

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);
string attack3(object me, object target, int damage);
string *hbmsg = ({
HBMAG "\n$N" HBMAG "大喝一声，双手分使两招，一起攻出。\n" NOR,
HBMAG "\n$N" HBMAG "双手齐出，分使不同招式，令人眼花缭乱。\n" NOR,
HBMAG "\n$N" HBMAG "左右手分使两招，毫不停滞，宛如两人同时攻出。\n" NOR,
HBMAG "\n$N" HBMAG "左手一招，右手一招，两招来路各异，令人难以低档！\n" NOR,
});
   
int perform(object me, object target)
{
        mapping buff, data;
        object weapon;
        int ap, dp, damage;
        string msg, myfam;
        int delta, delta2, time;
        int taoism,fmsk,xiantian,hb;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");
        
        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用" + name() + "。\n"); 

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 1000)
                return notify_fail("你的先天功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你没有激发先天功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你没有激发先天功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("你没有准备使用先天功，难以施展" + name() + "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        if( userp(me) ) 
        {
             if( (time = BUFF_D->get_buff_overtime(me, "xtg_xian")) > 0 )
                 return notify_fail(MAG"先天罡气消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        msg = HIW "\n$N" HIW "施出先天罡气，顿时将方圆十里天地之气吸入体内"
              "，凝聚于双手手掌处，左手一挥，层层叠叠涌向$n" HIW "！\n" NOR;

        addn_temp("apply/ap_power", 30, me);

        ap=attack_power(me,"unarmed")+me->query_con()*20;
        dp=defense_power(target,"parry")+target->query_dex()*20;
        
        delta = ABILITY_D->check_ability(me, "ap_power-xtg-xian"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        fmsk = me->query_skill("huajia-su",1);
        taoism = me->query_skill("taoism",1)/2000;
        xiantian = me->query_skill("xiantian-gong",1)/1000;
        hb = me->query_skill("zuoyou-hubo",1);
        
        damage = damage_power(me, "unarmed");
        damage+= damage_power(me, "force");     
        damage+= query("jiali", me);
        damage+= me->query_all_buff("unarmed_damage");
        damage+= damage / 300 * me->query_str();
                damage = damage*(taoism+xiantian);
        damage = damage - random(damage/2);
                
        if(target->query_family()=="古墓派")
        damage = damage - damage/5;

        if(target->query_family()=="欧阳世家")
        damage = damage + damage/5;
        delta2 = ABILITY_D->check_ability(me, "da_power-xtg-xian"); // 门派ab
        if( delta2 ) damage += damage*delta2/100;
        
        ap *= 2;
        if(target->query_family()=="古墓派")
        ap = ap - ap/5;
        if(target->query_family()=="欧阳世家")
        ap = ap + ap/5;
        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(2);
                
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 100+fmsk/10,
                                                    (: attack1, me, target, damage :));
        } else
        {
                msg += CYN "$n" CYN "倒吸一口凉气，飞身一跳，狼狈地躲过这招。\n" NOR; 
        }
        
        message_combatd(msg, me, target); 
        msg = HIW "紧接着，$N" HIW "一声清啸，右手虚向$n"HIW"盖下，庞大的天地之气汹涌般压向$n" HIW "！\n" NOR;
        
        ap=attack_power(me,"unarmed")+me->query_con()*20;
        dp=defense_power(target,"dodge")+target->query_dex()*20;

        if( delta ) ap += ap*delta/100;
        if(target->query_family()=="古墓派")
        ap = ap - ap/20;
        if(target->query_family()=="欧阳世家")
        ap = ap + ap/20;
        ap *= 2;
        if (ap / 2 + random(ap) > dp && living(target))
        {
                if( !target->is_busy() )
                        target->start_busy(2);
                        
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 200+fmsk/5,
                                                   (: attack2, me, target, damage :));
                if (random(me->query_skill("zuoyou-hubo",1)) > 500 
                && me->query_family()=="全真教"&&random(3)
                && (query("int", me)<25 || query("int", me)>39)
                && (!me->query_skill("count",1) || query("special_skill/capture", me))
                && living(target))
                {
                    msg += hbmsg[random(sizeof(hbmsg))];
                    msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 200+fmsk/5,
                                                   (: attack3, me, target, damage :));                  
                }
        } else
        {
                msg += CYN "$n" CYN "倒吸一口凉气，飞身一跳，狼狈地躲过这招。\n" NOR; 
        }
        
        message_combatd(msg, me, target);
        addn_temp("apply/ap_power", -30, me);

        addn("neili", -1000, me);
       
        time  = 38;
        time -= ABILITY_D->check_ability(me, "cd-xtg-xian"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd 
        if(wizardp(me) && query("id",me) =="mud") time =2;      
        buff =  
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "xtg_xian",
                "attr"   : "curse",
                "name"   : "先天功·先天罡气",
                "time"   : time,
                "buff_msg" : "先天罡气消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);
        
        me->start_busy(2 + random(2));

        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        target->receive_damage("jing", damage,me);
        target->receive_wound("jing", damage / 2,me);
                
        msg = HIR "结果$N" HIR "这掌正中$n" HIR "胸"
              "口，先天罡气登时贯脑而入，接连喷出数"
              "口鲜血。\n" NOR;
        set("neili", 0, target);
        msg += WHT "$n" WHT "只感到胸口一痛，全身真气宛若游丝，难受无比。\n" NOR;
        return msg;
}

string attack2(object me, object target, int damage)
{
        string msg;
        msg = HIR "结果$N" HIR "这掌正中$n" HIR "胸"
              "口，先天罡气登时贯体而入，接连喷出数"
              "口鲜血。\n" NOR;
        target->apply_condition("no_exert", 10);
        msg += WHT "$n" WHT "感到气脉受损，内息紊乱，说不出的痛苦。\n" NOR;
        return msg;
}
string attack3(object me, object target, int damage)
{
        string msg;
        msg = WHT "$n大惊之下，居然忘了躲闪招架，当即呆立在原地。\n"NOR;
        target->start_busy(5+random(4));
        return msg;
}
