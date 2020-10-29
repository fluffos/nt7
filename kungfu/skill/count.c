// count.c 阴阳八卦
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

int is_spsk() { return 1; }
string type() { return "knowledge"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

void skill_improved(object me) {}

int valid_learn(object me)
{
        int gift, mat;

        gift = 35;
        mat = 300;

        if( query("family/family_name", me) == "桃花岛" )
        {
                gift = 30;
                mat = 200;
        }

        if( !query("family/family_name", me) || 
            query("family/family_name", me) != "桃花岛" )
                return notify_fail("你不是桃花岛弟子，难以领会阴阳八卦的奥妙。\n");

        if( query("int", me)<gift )
                return notify_fail("你的先天悟性不足，难以领会阴阳八卦的奥妙。\n");

        if ((int)me->query_skill("mathematics", 1) < mat)
                return notify_fail("你的算术知识太差，无法理解阴阳八卦的奥妙。\n");

        if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("count", 1))
                return notify_fail("你的算术知识有限，无法理解更深奥的阴阳八卦。\n");

        if( me->query_skill("zuoyou-hubo",1) && !query("special_skill/capture", me) )
                return notify_fail("你的受到左右互博分心之术影响，难以领会阴阳八卦的奥妙。\n");

        return 1;
}


int practice_skill(object me)
{
        return notify_fail("阴阳八卦只能用学(learn)的来增加熟练度。\n");
}
int help(object me)
{
        write(HIC"\n阴阳八卦："NOR"\n");
        write(@HELP

    桃花岛弟子可以凭此技能查知玩家目前所在的位置。可以通过
阅读《河图》、《洛书》提高。
    请help location。

        学习要求：
                读书写字50级
                身为黄药师嫡传弟子
HELP
        );
        return 1;
}
