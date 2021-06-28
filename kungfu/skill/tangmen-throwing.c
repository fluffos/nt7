// This program is a part of NITAN MudLIB
// tangmen-throwing.c

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage == "throwing"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功心法火候不够，无法学唐门暗器。\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("你的轻功火候不够，无法领悟唐门暗器。\n");

        if( query("dex", me)<30 )
                return notify_fail("你的身法不够灵巧，无法学习唐门暗器。\n");

        if( query("str", me)<30 )
                return notify_fail("你的臂力不够，无法学习唐门暗器。\n");

        if( query("int", me)<28 )
                return notify_fail("你的悟性不够，无法学习唐门暗器。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("tangmen-throwing", 1))
                return notify_fail("你的基本暗器水平有限，难以领会更高深的唐门暗器。\n");

        return 1;
}

int practice_skill(object me)
{
//      object weapon;

        if( query("qi", me)<60 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练唐门暗器。\n");

        me->receive_damage("qi", 50);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tangmen-throwing/" + action;
}