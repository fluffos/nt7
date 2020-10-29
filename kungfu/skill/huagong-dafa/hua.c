// hua.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp;
        int my_max, tg_max;
        int suck;
        object weapon;

        if (target == me) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("在这里不能攻击他人。\n");

        if (! objectp(target))
                return notify_fail("你要化谁的内力？\n");

        if( query("race", target) != "人类" )
                return notify_fail("搞错了！只有人才能有内力！\n");

        if (me->is_busy())
                return notify_fail("你现在正忙，无法化他人内力。\n");

        my_max=query("max_neili", me);
        tg_max=query("max_neili", target);

        if ((int)me->query_skill("huagong-dafa", 1) < 100)
                return notify_fail("你的化功大法功力不够，不能施展！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够，不能施展化功大法。\n");

        if( query("max_neili", me)-me->query_all_buff("max_neili") >= 
            (me->query_neili_limit()-me->query_all_buff("max_neili"))*3 )
                return notify_fail("你的内力修为似乎已经达到了瓶颈，再吸取也是徒劳。\n"); 

        if( query("neili", target)<10 || 
            query("max_neili", target)<10 || query("no_suck", target) )
                return notify_fail(target->name() +
                                   "已然内力涣散，不必再化了。\n");

        if( query("max_neili", target)>query("max_neili", me)*10 )
                return notify_fail( target->name() +
                        "的内功修为远胜于你，你无法从化他的内力！\n");
                        
        if( !objectp(weapon=query_temp("weapon", me)) )
                message_combatd(HIR "$N" HIR "全身骨节爆响，双臂暴长数尺，手掌"
                        "刷的一抖，粘向$n！\n" NOR,
                        me, target);
        else
                message_combatd(HIR "$N" HIR "把手中的" + weapon->name() +
                                HIR "一扬，全身骨节爆响，双臂暴长数尺逼向$n" HIR + "，$p"
                                HIR "连忙架住。\n" NOR,
                                me, target);
                                
        if( target->query_skill("taixuan-gong", 1) )
        {
                message_sort(HIG "\n$N" HIG "刚将手掌接触到$n" HIG "肌肤，猛然觉得一股无比强大的"
                             "内劲反压回来，化功大法的内力却犹如石沉大海。$N" HIG "大吃一惊，连"
                             "忙将手缩回，再也不敢接近。\n" NOR);
                return 1;

        }

        //me->want_kill(target);
        
        if (living(target))
                if (! target->is_killing(me)) target->kill_ob(me);

        sp = attack_power(me, "force")+me->query_skill("bingchan-gong", 1);
        dp = defense_power(target, "dodge");

        if ((sp / 2 + random(sp) > random(dp)) || ! living(target))
        {
                suck = 1 + me->query_skill("huagong-dafa", 1) / 3;

		if( me->query_skill("bingchan-gong", 1) )
                   suck += suck* (me->query_skill("bingchan-gong",1)/100*4) /100; 
		
		if( me->query_family() == "星宿派" )
                        suck *= 2;
                        
                tell_object(target, HIR "你只觉天顶骨裂，全身功力"
                            "贯脑而出，如融雪般消失得无影无踪！\n" NOR);
                            
                addn("max_neili", -suck, target);
                addn("max_neili", suck, me);
                if( query("max_neili", target)<1 )
                        set("max_neili", 0, target);

                me->start_busy(2);
                target->start_busy(random(2));
        } else
        {       
                message_combatd(HIY "可是$p" HIY "看破了$P"
                                HIY "的企图，内力猛地一震，借势溜"
                                "了开去。\n" NOR, me, target);
                me->start_busy(3);
        }

        return 1;
}

