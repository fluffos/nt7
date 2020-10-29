// wudu-shengong.c 五毒神功
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
        return force == "hamagong" ||
               force == "xiuluo-yinshagong" ||
               force == "shunxi-qianli";
}

int valid_learn(object me)
{
        int nf;
        nf = (int)me->query_skill("force", 1);

        if ( nf < 10)
                return notify_fail("你的基本内功火候还不够，无法领会五毒神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("五毒神功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"wudu-shengong/" + func;
}
int help(object me)
{
        write(HIC"\n五毒神功："NOR"\n");
        write(@HELP

    五毒教必修的一门功夫，五毒弟子就是靠它才可以日夜与毒虫
毒药为伴。

        学习要求：
                基本内功10级
HELP
        );
        return 1;
}
