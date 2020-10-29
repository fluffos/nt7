// poison.c 基本毒技
// Last Modified by Lonely on Mar. 10 2000
// Modified by Java Mar.1998

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "poison"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        if( query("character", me) == "光明磊落" && 
            query("family/family_name", me) != "关外胡家" )
                return notify_fail("你心中暗想：我行事光明磊落，学什么毒技！\n");

        return 1;
}
/*
void skill_improved(object me)
{
        if ((me->query_skill("poison",1) == 50) ||
                (me->query_skill("poison",1) == 60) ||
                (me->query_skill("poison",1) == 70) ||
                (me->query_skill("poison",1) == 80) ||
                (me->query_skill("poison",1) == 90) ||
                (me->query_skill("poison",1) >= 100))
        {
                tell_object(me, "你体内的毒质开始反噬自身了，得找人散毒了。\n");
                me->apply_condition("poison_sandu",1000);
        }
}
*/
int practice_skill(object me)
{
        return notify_fail("基本毒技只能靠学习来提高。\n");
}
int help(object me)
{
        write(HIC"\n基本毒技："NOR"\n");
        write(@HELP

    星宿弟子下毒必具武功，下毒的效果和基本毒技的高低有很大
的关系。当体内毒素反噬自身时，得找人散毒。

        学习要求：
                名门正派的心法不能学
                非星宿派弟子不能学
HELP
        );
        return 1;
}
