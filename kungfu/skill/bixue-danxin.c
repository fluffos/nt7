#include <ansi.h>
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "丐帮"; }

int valid_learn(object me)
{        

        if( query("family/family_name", me) != family_name() )
                return notify_fail("碧血丹心只能丐帮弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}