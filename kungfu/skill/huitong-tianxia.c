#include <ansi.h>
// 
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "慕容世家"; }

int valid_learn(object me)
{        
        if (me->query_skill("canhe-zhi", 1) < 300)
                return notify_fail("你参合指火候不足，无法研习慧通天下。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("慧通天下只能慕容世家弟子方可研习。\n");

        if (me->query_skill("martial-cognize", 1) < 400)
                return notify_fail("你武学修养不足，无法研习慧通天下。\n");

        return 1;
}

int difficult_level()
{
        return 8000;
}