#include <ansi.h>
// 魔教 motun-tianxia
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "魔教"; }

int valid_learn(object me)
{        
        if (me->query_skill("chiyou-kuangzhanjue", 1) < 120)
                return notify_fail("你蚩尤狂战决火候不足，无法研习魔吞天下。\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("魔吞天下只能魔教弟子方可研习。\n");

        if (me->query_skill("moon-blade", 1) < 150)
                return notify_fail("你圆月弯刀修为不足，无法继续研习魔吞天下。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
