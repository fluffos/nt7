// xinghui-canlan.c 星辉灿烂
// By haiyan

inherit SKILL;
int is_pbsk() { return 1; }

int valid_enable(string usage) { return usage == "throwing"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("riyue-xinfa", 1) < 100)
                return notify_fail("你的内功心法火候不够，无法学星辉灿烂。\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("你的轻功火候不够，无法领悟星辉灿烂。\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法不够灵巧，无法领悟星辉灿烂。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("mantianhuayu-zhen", 1))
                return notify_fail("你的基本暗器水平有限，难以领会更高深的星辉灿烂。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练星辉灿烂。\n");

        me->receive_damage("qi", 45);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xinghui-canlan/" + action;
}
