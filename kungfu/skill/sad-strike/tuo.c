// This program is a part of NITAN MudLIB
// tuo.c
// 杨过决战金轮法王时所施展的决定胜负的一招。

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string name() { return HIM "拖泥带水" NOR; }

int perform(object me, object target)
{
        mapping buff;
        int damage;
        string msg;
        int ap, dp;
        string couple;
        object cob;
        int adp=0;
        int delta;
        int time;
        int fmsk,ngxy,flagremote;
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");
                
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if( query("static/marry", me)>1 )
                return notify_fail("你感情早已不纯，哪里还能领略到那种黯然销魂的感觉？\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的内功火候不够，使不出" + name() + "。\n");

        if ((int)me->query_skill("sad-strike", 1) < 180)
                return notify_fail("你的黯然销魂掌不够熟练，不会使用" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，无法使用" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "sad-strike")
                return notify_fail("你没有激发黯然销魂掌，无法使用" + name() + "。\n");

/*
        if( !stringp(couple=query("couple/couple_id", me)) )
                return notify_fail("你没有妻子，体会不到这种万念俱灰的感觉。\n");
*/
        /*
        if (! objectp(cob = find_player(couple)))
                return notify_fail("老婆不在啊，苦闷向谁发？\n");
        */
        if( userp(me) ) 
        {
            if( (time = BUFF_D->get_buff_overtime(me, "arxhz_tuo")) > 0 )
              return notify_fail(MAG"你刚刚施展完拖泥带水，现在心情没有那么郁闷了，还需等待"+time+"秒。\n"NOR);
        }
                
        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        fmsk = me->query_skill("taishang-wangqing",1);
        ngxy = me->query_skill("force-cognize",1);
        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");
        
        delta = ABILITY_D->check_ability(me, "ap_power-arxhz-tuo"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        me->start_busy(2);

        if (random(3) == 1 && query("max_neili", me) > 50000)
        {
            msg = HIR "$N" HIR "心下万念俱灰，凄然向妻子"
                      HIR "望了一眼，暗道：“别了！你自己保重。”\n"
                      "当下失魂落魄，随手一招，恰好使出了黯然销魂掌中"
                      "的「拖泥带水」。\n" NOR;
            ap += ap  / 5;
            if( query("can_perform/surge-force/new", me ) 
            && me->query_skill_mapped("force") == "surge-force"
            && fmsk > 500)
            ap *= 2;
        } else
        {
            msg = HIM "只见$N" HIM "没精打采的挥袖卷出，面无表情，随意拍出一掌，正是"
                      "黯然销魂掌中的「拖泥带水」。\n"NOR;
        }
        
        damage = damage_power(me, "unarmed");
        damage+= query("jiali", me);
        damage+= me->query_all_buff("unarmed_damage");
        damage+= damage / 300 * me->query_str();
        damage*= 2;
        
        flagremote = UNARMED_ATTACK;
        if(ngxy > 8000 & fmsk > 1000) flagremote = SPECIAL_ATTACK;      
        if(ngxy > 15000 & fmsk > 1800) flagremote = REMOTE_ATTACK;
        
        delta = ABILITY_D->check_ability(me, "da_power-arxhz-tuo"); // 门派ab
        if( delta ) damage += damage*delta/100;
        if(fmsk > 500) damage += damage /1000 * fmsk;
        
        if (query("can_perform/surge-force/new", me) 
        && me->query_skill_mapped("force") == "surge-force"
        && (random(3) > 1 || query("eff_qi", me)*100/query("max_qi", me) < 20 ) 
                && fmsk > 500)
        {
                msg += HIC "$N"HIC"仰天长啸，气势如山洪爆发，丹田内力迅速游遍全身！\n";
//              ap += ap / 3;
                damage += damage * 10;
                adp = 180;
        }       
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -30000, me);
                msg += COMBAT_D->do_damage(me, target, flagremote, damage, 200+fmsk/10+adp,
                                           HIR "只听$n" HIR "一声闷哼，“噗”的一"
                                           "声，这一掌正好击在$p" HIR "肩头。 \n"
                                           NOR);
        } else
        {
                addn("neili", -100, me);
                msg += HIC "可是$p" HIC "小心应付、奋力招架，挡开了这一招。\n"
                       NOR;
        }
        message_combatd(msg, me, target);  
        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-arxhz-tuo"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
        if( wiz_level(me) > 2) time = 2;        
        buff =  
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "arxhz_tuo",
                "attr"   : "curse",
                "name"   : "黯然销魂掌·拖泥带水",
                "time"   : time,
                "buff_msg" : "黯然销魂掌消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);
        return 1;
}

