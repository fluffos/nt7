#include <ansi.h>
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "密宗"; }

int valid_learn(object me)
{        
        if (me->query_skill("xuedao-daofa", 1) < 100)
                return notify_fail("你血刀大法火候不足，无法研习血影大法。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("血影大法只能密宗弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
