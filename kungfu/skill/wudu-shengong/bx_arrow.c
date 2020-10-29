// bx_arrow.c 碧血箭

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        string msg;
        int success, ap, dp;
        int delta;

        if( !objectp(target) ) target = offensive_target(me);
        
        if( !target || !target->is_character() || target == me ||        
            !me->is_fighting(target) ||
            !living(target) || query_temp("noliving", target) )
                return notify_fail("碧血箭只能在战斗中使用。\n");

        if( query("max_neili", me)<400 )
                return notify_fail("你的内力不够，不能有效施展碧血箭！\n");

        if( (int)me->query_skill("force",1) < 50 ||
                (int)me->query_skill("wudu-shengong",1) < 50 )
                return notify_fail("你的内功修为不够，不能有效施展碧血箭！\n");

        if( query("combat_exp", me)<query("combat_exp", target)/10 )
                return notify_fail("对方武功强你十倍，不会有用的，还是快跑吧！\n");

        message_combatd( HIC"$N双目血红，披头散发，仰天发出一声悲啸！\n\n$N把心一横，在自己舌尖狠命一咬，将毕生功力化做一道奇毒血箭向$n喷了过去！\n" NOR,me,target);

        success = 1;
        ap = me->query_skill("force",1)+me->query_skill("wudu-shengong",1);
        ap = ap /2 ;
        ap = ap * ap * ap/10;
        ap=ap+query("combat_exp", me);

        dp=query("combat_exp", target);

        delta = ABILITY_D->check_ability(me, "ap_power-wdsg-arrow"); // 门派ab
        if( delta ) ap += ap*delta/100;
        if( random(ap+dp) < random(dp) ) success = 0;

        ap=query("max_neili", me);
        dp=query("max_neili", target);

        if( delta ) ap += ap*delta/100;
        if( ap < random(dp) ) success = 0;

        if( success == 1 )
        {
                message_combatd(HIR"结果$n促不及防被血箭射个正着，顿时发出一声惨叫！$N见状哈哈大笑一声，眼前一黑倒在地上。\n" NOR,me,target);

                me->want_kill(target);
                target->kill_ob(me);
                me->kill_ob(target);
                addn("max_neili", -50, me);
                me->save();

                target->receive_wound("qi",query("max_qi", target)+1,me);
                target->receive_wound("jing",query("max_jing", target)+1,me);
                COMBAT_D->report_status(target);

                me->receive_wound("qi",query("max_qi", me)+1,target);
                me->receive_wound("jing",query("max_jing", me)+1,target);
                COMBAT_D->report_status(me);
        }
        else 
        {
                message_combatd(HIR"但是血箭被$n内力反震，化做一蓬血雾四散飘去！\n$N一声惨笑，长叹一声，眼前一黑倒在地上。\n" NOR,me,target);
                me->want_kill(target);
                target->kill_ob(me);
                me->kill_ob(target);

                addn("max_neili", -30, me);
                me->save();

                me->receive_wound("qi",query("max_qi", me)+1,target);
                me->receive_wound("jing",query("max_jing", me)+1,target);
                COMBAT_D->report_status(me);
        }

        return 1;
}
