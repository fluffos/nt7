// shangfei.c 伤肺诀

#include <ansi.h>

inherit F_SSERVER;

string name() { return "伤肺诀"; }

private void remove_effect(object me, int amount);

int perform(object me)
{
        string msg;
        object target;
        int skill, dodge_decrease;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「伤肺诀」只能在战斗中使用。\n");

        if( (int)query("neili", me) < 600 )
                return notify_fail("你的内力还不够高！\n");

        if( (int)me->query_skill("cuff") < 60 )
                return notify_fail("你的拳法还不到家，无法体现七伤拳的各种总诀！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 60)
                return notify_fail("你七伤拳的修为不够，不能够体会伤肺诀! \n");

        if( (int)me->query_skill("force", 1) < 60)
                  return notify_fail(HIM "你的基本内功修为不足，不能随便使用伤肺诀! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你没有激发七伤拳，无法运用伤肺诀！\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你没有准备使用七伤拳，无法施展「伤肺诀」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用此招！\n");


        msg = HIY "$N凝神定气，使出七伤拳总诀中的「" HIR "伤肺诀" HIY "」，双拳势如雷霆，向$n击去。\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -100, me);

                msg = HIG "$N的拳风隐含风雷，“澎”的一声打在$n身上！\n$n只觉得呼吸不顺，顿时脚步慢了许多！\n"NOR;
                dodge_decrease = query("apply/dodge", target) / 10;
                addn_temp("apply/dodge", -dodge_decrease, target);
                target->start_busy(2);
                me->start_busy(2 + random(2));
                call_out("remove_effect", skill/60, target, dodge_decrease);
        }
        else
        {
                msg = HIG "只见$n不慌不忙，轻轻一闪，躲过了$N的必杀一击！\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

private void remove_effect(object me, int amount)
{
        if (!me)
                return;
        addn_temp("apply/dodge", amount, me);
        tell_object(me, "你感觉呼吸变得顺畅，所中的七伤拳伤肺劲气逐渐消解了。\n");
}