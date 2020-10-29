// shenyuan-gong.c 神元功
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("shenyuan-gong", 1);
        return lvl /10 * lvl /10 * 20 * 15 / 10 / 20;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("shenyuan-gong", 1);
        if( query("gender", me) == "无性" && lvl>49 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的神元功。\n");
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本内功火候还不够，无法领会神元功。\n");
        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("神元功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"shenyuan-gong/" + func;
}
int help(object me)
{
        write(HIC"\n神元功："NOR"\n");
        write(@HELP

    神元功是江南姑苏慕容世家的本门内功。

        学习要求：
                基本内功10级
HELP
        );
        return 1;
}
