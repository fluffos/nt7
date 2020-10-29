// taoism.c 道学心法
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        int lvl;

        lvl = (int)me->query_skill("taoism", 1);

        if( query("gender", me) == "无性" && lvl>19 )
                return notify_fail("你刚听一会儿，便觉心智迷糊，原来你没有阳刚之\n"
                           "气，无法领会里面的阴阳变化之道。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("道学心法只能靠学习来提高。\n");
}

int help(object me)
{
        write(HIC"\n道学心法："NOR"\n");
        write(@HELP

    太上道祖传下的道德真言五千字中蕴涵的博大精深的心法。
    可寻找道德经阅读。

        学习要求：
                与禅宗心法、密宗心法、紫氲吟、正气诀和基本毒技不能兼学
HELP
        );
        return 1;
}
