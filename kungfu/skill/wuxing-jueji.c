// wuxing-jueji.c 五行绝技

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage == "throwing"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功心法火候不够，无法学五行绝技。\n");

        if ((int)me->query_skill("dodge") < 80)
                return notify_fail("你的轻功火候不够，无法领悟五行绝技。\n");

        if ((int)me->query_dex() < 26)
                return notify_fail("你的身法不够灵巧，无法领悟五行绝技。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("wuxing-jueji", 1))
                return notify_fail("你的基本暗器水平有限，难以领会更高深的五行绝技。\n");

        return 1;
}

int practice_skill(object me)
{
//      object weapon;

        if( query("qi", me)<60 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练五行绝技。\n");

        me->receive_damage("qi", 52);
        addn("neili", -35, me);
        return 1;
}