#include <ansi.h>
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "神龙教"; }

int valid_learn(object me)
{        
        if (me->query_skill("busi-shenglong", 1) < 120)
                return notify_fail("你不死神龙火候不足，无法研习神龙大法。\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("神龙大法只能神龙教弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
