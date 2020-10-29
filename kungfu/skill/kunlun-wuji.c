#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "昆仑派"; }

int valid_learn(object me)
{        
        if (me->query_skill("qiankun-jian", 1) < 120)
                return notify_fail("你乾坤神剑火候不足，无法研习昆仑无极。\n");        

        if( query("family/family_name", me) != family_name() )
                return notify_fail("昆仑无极只能昆仑派弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}