// heal.c
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
        if( me->is_fighting() )
                return notify_fail("战斗中运功疗伤？找死吗？\n");

        if( me->is_busy() )
                return notify_fail("你现在正忙着呢，哪有空运功？\n");

        if( (int)me->query_skill("baiyun-xinfa", 1) < 20)
                return notify_fail("你的白云心法修为还不够。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真气不够。\n");
/*
        if( query("eff_qi", me) >= query("max_qi", me) )
                return notify_fail(HIR"你没有受伤，不必运真气疗伤！\n"NOR);
*/
        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");

        write( HIW "你全身放松，坐下来运起白云心法开始疗伤。\n" NOR);
        message("vision",
                HIW + me->name() + "坐下运功疗伤，头顶白雾缭绕，半响后吐出一口浊气，气色已恢复正常。\n" NOR, environment(me), me);

        me->receive_curing("qi", 10 + (int)me->query_skill("force")/5 );
        addn("neili", -50, me);
        set("jiali", 0, me);
        me->start_busy(1);

        return 1;
}
int help(object me)
{
        write(WHT"\n白云心法之自疗："NOR"\n");
        write(@HELP

        使用功效：
                为自己疗伤

        出手要求：
                白云心法20级
                内力50
HELP
        );
        return 1;
}