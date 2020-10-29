// mahayana.c 大乘涅磐功
//Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        if( query("shen", me)<0 )
                return notify_fail("你的邪气太重，无法修炼大乘涅磐功。\n");

        return 1;
}

void skill_improved(object me)
{
        if ((int)me->query_skill("mahayana", 1) >= 100 &&
            !query("sl_gift/mhyn", me) && query("gender", me) != "男性" )
        {
                addn("dex", 1, me);
                set("sl_gift/mhyn", 1, me);
                tell_object(me, HIM "\n你的大乘涅磐功学有所成，提高了你的身法。\n" NOR);
        }
}

int help(object me)
{
        write(HIC"\n大乘涅磐功："NOR"\n");
        write(@HELP

    峨嵋派素不喜与人争斗，弟子门人常常闭门修炼以增长人体潜
能，其有效程度乃取决于佛法修为（即大乘涅磐功的等级）。打坐
静修可在峨嵋禅房使用命令jingzuo。请help jingzuo。

        学习要求：
                相应的临济十二庄
                不能学禅宗心法外的其他宗教心法
HELP
        );
        return 1;
}
