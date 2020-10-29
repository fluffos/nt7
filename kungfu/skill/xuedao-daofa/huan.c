// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "我必还之" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        object weapon;
        string msg;
        int ap, dp, damage;
        int per;
        int delta, time;
        int fmsk = me->query_skill("xueying-dafa", 1);

        /*
        if( query("family/family_name", me) != "血刀门" )
                return notify_fail("你不是血刀门弟子，无法使用" + name() + "。\n");
        */

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用" + name() + "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 1000)
                return notify_fail("你的血刀大法还不到家，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你没有激发血刀大法为刀法，难以施展" + name() + "。\n");

        if( query("qi", me)<100 )
                return notify_fail("你目前气血翻滚，难以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你目前真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "xddf_huan")) > 0 )
                        return notify_fail(MAG"我必还之消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        
        delta = ABILITY_D->check_ability(me, "ap_power-xddf-huan"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        msg = HIR "$N" HIR "手中" + weapon->name() + "直指$n" HIR"，口中喝骂道：「洒家什么都吃就是不知亏！人若伤我！我必还之！」\n"
              HIR "只见" + weapon->name() + "泛出浓烈血光、腥味刺鼻，映的四周直若浓血地狱。\n";

        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                target->set_weak(5);
                per=query("eff_qi", me)*100/query("max_qi", me);
                if (per>100) per=101;
                if (per > 60)
                {
                        damage = damage_power(me, "blade");
                        damage+= query("jiali", me);
                        damage*= 6;
                }
                else
                if (per < 30)
                        damage = -1;
                else
                        damage=query("max_qi", target)/100*per;

                addn("neili", -150, me);
                me->start_busy(2);

                if (damage > 0)
                  msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300+fmsk / 15,
                                           HIR "在$n" HIR "眼中，" + weapon->name() + "的刀尖越来越大、压的自己几乎透不过气，"
                                           HIR "直至猛然一呕血，却发现" + weapon->name() + "已经在自己身上留下狰狞的轨迹。\n" NOR);
                else
                {
                        msg += HIR "在$n" HIR "眼中，" + weapon->name() + "的刀尖越来越大、压的自己几乎透不过气，"
                               HIR "直至猛然一呕血，却发现" + weapon->name() + "已经在自己身上留下狰狞的轨迹。\n" NOR;
                        target->die(me);
                }
        } else
        {
                me->start_busy(2);
                msg += CYN "正当这刀要落在$n" CYN "身上，$N" CYN "浑身一颤，血光骤减，$n" CYN "顺势滚到一旁，已是不成招法，躲过了$N"
                       CYN "的必杀一刀。\n"NOR;
                addn("neili", -100, me);
        }
        
        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-xddf-huan"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
                
        buff =  
	([
	        "caster" : me,
	        "target" : me,
	        "type"   : "cooldown",
	        "type2"  : "xddf_huan",
	        "attr"   : "curse",
	        "name"   : "血刀大法·我必还之",
	        "time"   : time,
	        "buff_msg" : "我必还之消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
	        "disa_msg" : "",
	        "disa_type": 0,
	]);
	BUFF_D->buffup(buff);

        message_combatd(msg, me, target);
        return 1;
}

