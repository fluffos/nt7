// maxsuck.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp;
        int my_max, tg_max;
        int sucked;
        object weapon;

        if (! target || target == me) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("在这里不能攻击他人。\n");

        if (! objectp(target) || ! me->is_fighting(target))
                return notify_fail("你要吸取谁的丹元？\n");

        if( query("race", target) != "人类" || 
            query("not_living", target) )
                return notify_fail("搞错了！只有活着的生物才能有丹元！\n");

        my_max=query("max_neili", me);
        tg_max=query("max_neili", target);
        if ((int)me->query_skill("beiming-shengong", 1) < 90)
                return notify_fail("你的北冥神功功力不够，不能吸取对方的丹元！n");

        if( query("neili", me) < 20 )
                return notify_fail("你的内力不够，不能使用北冥神功。\n");

        if( ((int)me->query_neili_limit()-me->query_all_buff("max_neili"))*3 <= 
            my_max-me->query_all_buff("max_neili"))
                return notify_fail("你的内功水平有限，再吸取也是徒劳。\n");

        if( query("max_neili", target)<100 || query("no_suck", target) )
                return notify_fail( target->name() +
                        "丹元涣散，功力未聚，你无法从他体内吸取任何东西！\n");

        if( query("max_neili", target)<query("max_neili", me)/20 )
                return notify_fail( target->name() +
                        "的内功修为远不如你，你无法从他体内吸取丹元！\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                message_combatd(HIG "$N" HIG "全身一振，伸出右手，轻轻握在$n"
                        HIG "的手臂上。\n\n" NOR, me, target);
        else
                message_combatd(HIR "$N" HIR "把手中的" + weapon->name() +
                                HIR "一扬，伸出右手逼向$n" HIR + "，$p"
                                HIR "连忙架住。\n" NOR,
                                me, target);
        
        if( target->query_skill_mapped("force") == "taixuan-gong" )
        {
                tell_object(target, HIW + me->name() + HIW "伸出右手，轻轻握在你的手"
                             "臂上，试图吸取你的内力，但是你体内的太玄真气猛地将"
                             "其反弹回去。\n");

                return notify_fail(HIG "你伸出右手，轻轻握在" + target->name() +
                                   HIG "的手臂上，却猛的感觉一股内劲将你的手弹回。\n" NOR);
        }                

        if( living(target) && !target->is_killing(me) )
        {
                me->want_kill(target);
                target->kill_ob(me);
        }

        sp = me->query_skill("force");
        dp = target->query_skill("force");

        if( (sp + random(sp) > dp + random(dp) ) || ! living(target) )
        {
                tell_object(target, HIR "你只觉全身乏力，全身功力如"
                            "融雪般消失得无影无踪！\n" NOR);
                tell_object(me, HIG "你觉得" + target->name() +
                            HIG "的丹元自手掌源源不绝地流了进来。\n" NOR);

                sucked = 1 + me->query_skill("beiming-shengong", 1) / 3;
                
                if( me->query_skill("xiaoyao-you",1 ) > 100 )
                        sucked += sucked* (me->query_skill("xiaoyao-you",1)/100*4) /100; 
                        
                if( me->query_family() == "逍遥派" )
                        sucked *= 2;
                        
                addn("max_neili", -sucked, target);
                addn("max_neili", sucked, me);
                if( query("max_neili", target)<1 )
                        set("max_neili", 0, target);

                me->start_busy(2);
                target->start_busy(2);
                addn("neili", -10, me);
        }
        else
        {       
                message_combatd(HIY "可是$p" HIY "看破了$P" HIY
                                "的企图，机灵地溜了开去。\n" NOR,
                                me, target);
                me->start_busy(3);
        }

        return 1;
}

