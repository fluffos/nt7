// huntian-qigong.c 混天气功

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int valid_force(string force)
{
        return 1;
        return force == "jiaohua-neigong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huntian-qigong", 1);
        return lvl * lvl * 15 * 9 / 100 / 200;
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 30)
                return notify_fail("你的基本内功火候不够，无法学习混天气功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("混天气功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huntian-qigong/" + func;
}

int help(object me)
{
        write(HIC"\n混天气功："NOR"\n");
        write(@HELP

    混天气功为丐帮本门内功。

        学习要求：
                学混天气功，要不正不邪、亦正亦邪
HELP
        );
        return 1;
}
