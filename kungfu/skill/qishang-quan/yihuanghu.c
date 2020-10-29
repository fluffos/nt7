// yihuanghu.c 意恍惚诀

#include <ansi.h>

inherit F_SSERVER;

string name() { return "意恍惚诀"; }

int perform(object me)
{
        string msg;
        object target;
        int skill;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「意恍惚诀」只能在战斗中使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if( (int)query("neili", me) < 1000 )
                return notify_fail("你的内力还不够高！\n");

        if( (int)me->query_skill("cuff") < 150 )
                return notify_fail("你的拳法还不到家，无法体现七伤拳的各种总诀！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 150)
                return notify_fail("你七伤拳的修为不够，不能够体会意恍惚诀! \n");

          if( (int)me->query_skill("force", 1) < 150)
                  return notify_fail(HIM "你的基本内功修为不足，不能随便使用意恍惚诀! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你没有激发七伤拳，无法运用意恍惚诀！\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你没有准备使用七伤拳，无法施展「意恍惚决」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用此招！\n");


        msg = HIY "$N凝神定气，使出七伤拳总诀中的「" HIR "意恍惚诀" HIY "」，双拳势如雷霆，向$n击去。\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -300, me);

                msg = HIC "结果$N双拳击中时，却是若有若无。\n$n正在奇怪间，已被$N的真气制住，神情恍恍忽忽的！\n"NOR;
                target->start_busy(ap/80+2);
                me->start_busy(1);
        }
        else
        {
                msg = HIG "只见$n不慌不忙，轻轻一闪，躲过了$N的必杀一击！\n"NOR;

                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}