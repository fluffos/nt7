// lamaism.c 密宗心法
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

        lvl = (int)me->query_skill("lamaism", 1);

        if( query("class", me) != "bonze" && query("family/family_name", me) != "段氏皇族" && lvl>39 )
                return notify_fail("你未入佛门，尘缘不断，无法继续修持密宗神法。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("密宗心法只能靠学(learn)来提高。\n");
}

int help(object me)
{
        write(HIC"\n密宗心法："NOR"\n");
        write(@HELP

    密宗心法是雪域密宗心法，用以超渡生灵。

        学习要求：
                不可学禅宗、道家和华山的心法以及星宿毒技
HELP
        );
        return 1;
}
