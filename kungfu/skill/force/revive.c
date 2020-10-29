// revive.c
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;
//inherit SSERVER;

int exert(object me, object target)
{
        int n, t;

        if (me != target)
                return notify_fail("你只能用内功恢复自己的体力。\n");

        if( query("neili", me)<20 )
                return notify_fail("你的内力不够。\n");

        t=query("max_tili", me)-query("tili", me);
        if (t < 10)
                return notify_fail("你现在体力充沛。\n");
        n = me->query_skill("force");
        if (n < 20) n = 20;
        if( query("neili", me)<n)n=query("neili", me);

        addn("neili", -n, me);
        addn("tili", (n/10), me);
        if( query("tili", me)>query("max_tili", me) )
                set("tili",query("max_tili",  me), me);
        
        message_combatd("$N吸了口气，丹田真气游走四肢，全身也渐渐有了力气。\n", me);

        if( me->is_fighting() ) me->start_busy(1);
        
        return 1;
}
int help(object me)
{
        write(WHT"\n基本内功之补充体力："NOR"\n");
        write(@HELP

        使用功效：
                补充自己消耗的体力　

        出手要求：
                基本内功
                内力20
HELP
        );
        return 1;
}
