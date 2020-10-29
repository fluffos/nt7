//banruo-zhang's perform yipai(一拍两散)
//mud@NT7 2015.02.15 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
string name() { return HIW "一拍两散" NOR; }
int perform(object me, object target)
{
        int damage,count = 0;
        int max_neili,neili;
        int ap,dp;
        string msg;
        int lunhui,budd,yjj,banruo;
                int flagremote = 0;
        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法施展" + name() + "。\n");
       
        if( !objectp(target) ) target = offensive_target(me);
        
        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) 
           || environment(target)!=environment(me))
                return notify_fail("一拍两散绝招只能对战斗中的对手使用。\n");
                
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能使用「一拍两散」！\n");       
        if( (int)me->query_skill("buddhism", 1) < 5000 )
                return notify_fail("你的佛法造诣太低，不能使用一拍两散绝招对敌！\n");
                
        if( (int)me->query_skill("banruo-zhang", 1) < 1800 )
                return notify_fail("你的般若掌还不够熟练，不能使用一拍两散绝招对敌！\n");
                
        if( me->query_skill("yipai-liangsan", 1) < me->query_skill("banruo-zhang", 1)-100 )
                return notify_fail("你的一拍两散还不够熟练，不能使用一拍两散绝招对敌！\n");
                
        if( me->query_skill("yijinjing", 1) < me->query_skill("banruo-zhang", 1)-100 )
                return notify_fail("你的易筋经功还不够熟练，不能使用一拍两散绝招对敌！\n");
        if( (int)me->query_skill("strike", 1) < 1800 )
                return notify_fail("你的掌法不够娴熟，使不出般若掌的绝招！\n");
        if (me->query_skill_mapped("force") != "yijinjing")
                return notify_fail("你必须使用易筋经才能发挥一拍两散的威力。\n");
                
        if (me->query_skill_prepared("strike") != "banruo-zhang" &&
            me->query_skill_mapped("strike") != "banruo-zhang")
                return notify_fail("你必须先将般若掌运用于掌法之中才行。\n");
//        if (me->query_skill_mapped("parry") != "banruo-zhang")
//                return notify_fail("你必须先将般若掌运用于招架之中才行。\n");
                                
        max_neili = query("max_neili",me);
        neili = query("neili",me);
        if( max_neili < 10000000 )
                return notify_fail("你内力修为不足，使不出般若掌的绝招！\n");     
        if( neili < max_neili/2 )
                return notify_fail("你现在内力不足，使不出般若掌的绝招！\n");     
             
        me->start_busy(2+random(2));
        if(!target->is_busy())
                target->start_busy(1); 
        
        ap = attack_power(me,"strike");
        ap+= attack_power(me,"force");
        ap+= me->query_skill("buddhism",1);
        
        dp = defense_power(target,"parry");
        dp+= defense_power(target,"dodge");
        
        lunhui = me->query_skill("lunhui",1);
        budd = me->query_skill("buddhism",1);
        banruo = me->query_skill("banruo-zhang",1);
        yjj = me->query_skill("yijinjing",1);
        
        budd = budd/5000;
        if(budd<1) budd = 1;
        if(budd>12) budd = 12;
        
        yjj = yjj/2000;
        if(yjj<1) yjj=1;
        if(yjj>10) yjj=10;
        
        ap = ap + ap * lunhui/1000;
        
        message_combatd(sort_msg(HIY "$N" HIY "大喝道：“吃我一掌！”。双掌自外向里转了个圆圈，"
             "缓缓向$n推了过来。$N掌力未到，$n已感胸口呼吸不畅，顷刻之间，$N的掌力如怒潮般汹涌而至。\n" NOR), me, target);
        message_combatd(HIY+HBRED"【一拍两散】！\n"NOR,me);
        if(ap/2+random(ap) > dp)
        {
            damage = damage_power(me,"strike");
            damage+= damage_power(me,"force");
            damage+= me->query_skill("force-cognize",1);
            damage+= query("jiali",me);
            damage*= budd+yjj;
            msg = HIY"$N高宣佛号";
            if(me->query_skill("yijinjing",1)> banruo-100)
            {
               damage+= damage;
               msg+= "运起"HIR"易筋经神功"NOR+HIY",将";
               count+=1;
            }
            if(me->query_skill("luohan-quan",1)> banruo-100)
            {
               damage+= damage;
               msg+= HIR"罗汉拳，";
               count+=1;
            }
            if(me->query_skill("nianhua-zhi",1)> banruo-100)
            {
               damage+= damage;
               msg+= HIR"拈花指，";
               count+=1;
            }
            if(me->query_skill("qianye-shou",1)> banruo-100)
            {
               damage+= damage;
               msg+= HIR"如来千叶手，";
               count+=1;
            }
            if(me->query_skill("sanhua-zhang",1)> banruo-100)
            {
               damage+= damage;
               msg+= HIR"散花掌，";
               count+=1;
            }
            if(me->query_skill("yizhi-chan",1)> banruo-100)
            {
               damage+= damage;
               msg+= HIR"一指禅，";
               count+=1;               
            }
            if(me->query_skill("yipai-liangsan",1)> banruo-100)
            {
               damage+= damage;
               msg+= HIR"一拍两散"HIY"等少林绝技一一融合，功力大增！\n";
               count+=1;               
            }
            if(target->is_bad())
            {
               damage = damage + damage/2;
               msg+= HIC"$N想起$n生平所作所为皆为奸恶之举，掌力又加了五成！\n";
            }
            if(budd == 12) count+=1;
            if(count == 8 && random(3)) 
            {
               if(random(budd)> 4 && damage < query("max_qi",target))
               damage = query("max_qi",target);
               else if (damage < query("max_qi",target)/2)
               damage = query("max_qi",target)/2;
               addn("neili",-max_neili/2,me);
               msg+= NOR+RED"$N"NOR+RED"孤注一掷，将全身功力汇于一掌之内拍出，成败在此一举！\n";
            }
            message_combatd(sort_msg(msg), me, target); 
            if(random(budd) > 3 || budd == 12)
                        {
                            if(random(100) < 85)
                                flagremote = 1;
                                else if(banruo > 12000)
                                flagremote = 1;
                        }
                        if(query("sex/times",me))
                        damage = damage / 2 ;
            if(query("combat_exp",me) /3*2 + random( query("combat_exp",me)) > query("combat_exp",target))
            msg = COMBAT_D->do_damage(me, target, (flagremote ? REMOTE_ATTACK : UNARMED_ATTACK), damage, 100 + lunhui/5, 
                  HIY"$n猝不及防，被这排山倒海般的掌力重重击中，顿时魂飞魄散！\n"NOR);       
            else
            msg = COMBAT_D->do_damage(me, target, (flagremote ? REMOTE_ATTACK : UNARMED_ATTACK), damage/2, 100 + lunhui/5,
                  HIY"两股掌力相交，嗤嗤有声，$N和$n均退了三步。$n一霎间只感全身乏力，真气提不上来!\n"NOR);
            
            addn("neili", -max_neili/budd,me);
        }
        else
        {
            msg = CYN "$n" CYN "倒吸一口凉气，飞身一跳，狼狈地躲过这招。\n" NOR;
            addn("neili", -max_neili/40,me);
        }
        if(query("neili",me) < 0) me->set("neili",0);
        message_combatd(msg, me, target);
        if(wizardp(me) && query("id",me)=="mud") tell_object(me,"count:damage="+count+":"+damage+"\n");
        return 1;
}

