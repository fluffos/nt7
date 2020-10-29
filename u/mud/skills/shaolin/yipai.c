//banruo-zhang's perform yipai(一拍两散)
//mud@NT7 2015.02.15 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";
string name() { return HIW "一拍两散" NOR; }

int perform(object me, object target)
{
        int damage;
        int max_neili,neili,jiali;
        int ap,dp;
        string msg;
        int lunhui,budd;

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法施展" + name() + "。\n");
       
        if( !objectp(target) ) target = offensive_target(me);
        
        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) 
           || environment(target)!=environment(me))
                return notify_fail("一拍两散绝招只能对战斗中的对手使用。\n");      


        if( (int)me->query_skill("banruo-zhang", 1) < 180 )
                return notify_fail("你的般若掌还不够熟练，不能使用一拍两散绝招对敌！\n");

        if( (int)me->query_skill("yijinjing", 1) < 180 )
                return notify_fail("你的易筋经功还不够熟练，不能使用一拍两散绝招对敌！\n");
 
        if( (int)me->query_skill("strike", 1) < 180 )
                return notify_fail("你的掌法不够娴熟，使不出般若掌的绝招！\n");
                
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「一拍两散」！\n");
                                
        if (me->query_skill_prepared("strike") != "banruo-zhang" ||
            me->query_skill_mapped("strike") != "banruo-zhang")
                return notify_fail("你必须先将般若掌运用于掌法之中才行。\n");

//        if (me->query_skill_mapped("parry") != "banruo-zhang")
//                return notify_fail("你必须先将般若掌运用于招架之中才行。\n");
                                
        max_neili = me->query("max_neili");
        neili = me->query("neili");
        if( max_neili < 100000 )
                return notify_fail("你内力修为不足，使不出般若掌的绝招！\n");     
        if( neili < max_neili/10*9 )
                return notify_fail("你现在内力不足，使不出般若掌的绝招！\n");     

        if( (int)me->query("jingli") < me->query("eff_jingli")/2 )
                return notify_fail("你现在精力不足，使不出般若掌的绝招！\n");   
                
        tell_object(me, RED"你孤注一掷，将全身功力汇于一掌之内拍出！\n"NOR);
        me->start_busy(1+random(2));

        if(!target->is_busy())
                target->start_busy(1); 
      
        jiali = me->query("neili")/4;
        me->set_temp("brz_yipai", me->query("jiali")+1);
        me->set("jiali", jiali);      
                
        if(wizardp(me))  tell_object(me, "Jiali = "+jiali+"。");

        ap = attack_power(me,"strike");
                ap+= attack_power(me,"force");
                ap+= me->query_skill("buddhism",1);
                
                dp = defense_power(target,"parry");
                dp+= defense_power(target,"dodge");
                
                lunhui = me->query_skill("lunhui",1);
                budd = me->query_skill("buddhism",1);
                budd = budd/5000;
                if(budd<1) budd = 1;
                if(budd>6) budd = 12;
                ap = ap + ap * lunhui/1000;
                ap*= 2;
                
                damage = damage_power(me,"strike");
                damage+= damage_power(me,"force");
                damage+= me->query_skill("force-cognize",1);
                damage*= budd;
                
                message_combatd(sort_msg(HIY "\n$N" HIY "大喝道：“吃我一掌！”双掌自外向里转了个圆圈，"
                         "缓缓向$n推了过来。\n$N掌力未到，$n已感胸口呼吸不畅，顷刻之间，$N的掌力如怒潮般汹涌而至。" NOR), me);

        if(ap/2+random(ap) > dp)
        {
            if(query("combat_exp",me) /2 + random( query("combat_exp",me)) > query("combat_exp",target))
            msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 100 + lunhui/5, 
                              HIY"$n猝不及防，被这排山倒海般的掌力重重击中，魂飞魄散！\n"NOR);       
            else
            msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage/2, 100 + lunhui/5,
                  HIY"两股掌力相交，嗤嗤有声，$N和$n均退了三步。$n一霎间只感全身乏力，真气提不上来!\n"NOR);
        }
        else
        msg = CYN "$n" CYN "倒吸一口凉气，飞身一跳，狼狈地躲过这招。\n" NOR;
        // cost all neili and half jingli.
        me->set("neili", max_neili/2);
        me->set("jiali", me->query_temp("brz_yipai")-1);
        me->delete_temp("brz_yipai");
        me->set("jingli", me->query("eff_jingli")/5);
        
        message_combatd(msg, me, target);
            me->stary_busy(1+random(2));
        if(!target->is_killing(me->query("id"))) target->kill_ob(me); // hehehehehehe.....
        return 1;
}


