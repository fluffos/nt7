// poqizhen.c 破气针
 
#include <ansi.h>
 
inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("shigu-bifa",1);

        if( !(me->is_fighting() ))
                return notify_fail("「制气」只能在战斗中用在对手身上。\n");
 
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "dagger" )
                return notify_fail("你使用的武器不对。\n");

        if( skill < 80)
                return notify_fail("你的子母针法不够纯熟, 不能使用「」！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的内力不够，无法运用「制气」！\n");
 
        msg = HIR "$N大笔一起，向$n丹田连点三点，正是那“裴”字的起首三笔，自上而下的划将下来。\n";
        message_vision(msg, me, target);
 
        ap = me->query_skill("dagger") + skill;
        dp = target->query_skill("force") / 3;
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp )
        {
                if(userp(me))
                        addn("neili", -100, me);
                msg = HIR"$N笔尖丝毫不差的点中对方要害, $n顿时觉得丹田上一阵刺痛，\n";
                msg += HIR"全身真气狂泄而出！\n" NOR;

                neili_wound = 1000 + random(skill);
                if( neili_wound>query("neili", target) )
                        neili_wound=query("neili", target);

                qi_wound = neili_wound / 5;
                if( qi_wound>query("qi", target) )
                        qi_wound=query("qi", target);
                if(qi_wound < 0) qi_wound = 0;

                addn("neili", -neili_wound, target);
                addn("qi", -qi_wound, target);
                addn("eff_qi", -qi_wound, target);
                target->start_busy(3);me->start_perform( 4+random(3), "「制气」");
}
        else
        {
                if(userp(me))
                        addn("neili", -80, me);
                msg = HIW"可是$n瞬间反应过来，腾挪跳跃，躲过了这次重创。\n"NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);

        return 1;
}