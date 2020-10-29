// qimen-wuxing 奇门五行
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

int is_spsk() { return 1; }
string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

//int valid_enable(string usage) { return usage=="taoism"; }
int practice_skill(object me)
{
        return notify_fail("奇门五行能靠学(learn)来提高。\n");
}
int valid_learn(object me)
{
        if ((int)me->query_skill("mathematics", 1) < 200)
                return notify_fail("你的算术知识太差，无法理解奇门五行的奥妙。\n");

        if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("qimen-wuxing", 1))
                return notify_fail("你的算术知识有限，无法理解更深奥的奇门五行。\n");

        return 1;
}

/*
string conjure_magic_file(string spell)
{
        return __DIR__ + "qimen-wuxing/" + spell;
}
*/
int help(object me)
{
        write(HIC"\n奇门五行："NOR"\n");
        write(@HELP


    是东海桃花岛的独门功夫。相传桃花岛虽然地处海外，人迹罕
至，但岛上却是家传渊博，对奇门五行研究得很深。有了这门功夫，
再配上桃花岛的布阵箱就可以摆出奇门五行阵，把敌人困在阵内。

    array somebody  在布阵箱的配合下，可以对某人布阵，使其
身陷阵内。

    可以阅读《易经》系列书籍提高。


        学习要求：
                不能同时修习左右互博之术
HELP
        );
        return 1;
}
