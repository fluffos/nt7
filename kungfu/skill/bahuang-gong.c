// bahuang-gong.c 八荒六合唯我独尊功
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_enable(string usage) { return usage == "force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_force(string force)
{
        return 1;
        return force == "xiaoyao-xinfa" ||
               force == "lingjiu-xinfa" ||
               force == "beiming-shengong" ||
               force == "xiaowuxiang" ||
               force == "wudoumi-shengong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bahuang-gong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 80)
                return notify_fail("你的基本内功火候还不够。\n");

        if( query("gender", me) == "无性" && 
        (int)me->query_skill("bahuang-gong", 1) > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的八荒六合唯我独尊功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("八荒六合唯我独尊功只能用学(learn)的来提高。\n");
}
string exert_function_file(string func)
{
        return __DIR__"bahuang-gong/" + func;
}

int help(object me)
{
        write(HIC"\n八荒六合唯我独尊功："NOR"\n");
        write(@HELP

    八荒六合唯我独尊功是灵鹫宫至高无上的内功，须以最上乘内
功为根基。这功夫威力奇大，却有一个大大的不利之处，每三十年，
便要返老还童一次。

        学习要求：
                灵鹫宫弟子
                基本内功10级
HELP
        );
        return 1;
}
