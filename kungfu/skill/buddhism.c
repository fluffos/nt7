// buddhism.c 禅宗心法
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
        if( query("guilty", me)>0 )
                return notify_fail("你屡犯僧家数戒，尘俗之心太重，无法修炼禅宗心法。\n");

        if( query("class", me) != "bonze" && me->query_skill("buddhism",1) >= 350 )
                return notify_fail("你凡心重，不出家，怎么能继续修炼禅宗心法。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("禅宗心法只能靠学(learn)来提高。\n");
}

void skill_improved(object me)
{
        if( me->query_skill("buddhism",1) == 120 && !query("sl_gift/int", me) )
        {
                addn("int", 1, me);
                set("sl_gift/int", 1, me);
                tell_object(me, HIM "\n你的禅宗心法学有所成，提高了你的智力。\n" NOR);
        }
}

int help(object me)
{
        write(HIC"\n禅宗心法："NOR"\n");
        write(@HELP

    少林弟子的必修课。少林派创派祖师达摩乃是天竺禅宗大师，
又是东土禅宗第一祖，少林弟子自应以修习禅宗，精研佛法为任。
配合混元一气功可以长精，精增加的程度取决于混元一气功和禅宗
心法等级的高低。

        学习要求：
                犯戒或非出家人无法领悟
                与道家心法和紫氲吟不能兼学
HELP
        );
        return 1;
}
