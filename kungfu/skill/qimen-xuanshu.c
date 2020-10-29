#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "桃花岛"; }

int valid_learn(object me)
{        
        
        if (me->query_skill("qimen-wuxing", 1) < 100)
                return notify_fail("你奇门五行掌握得不够。\n");

        if( query("family/family_name", me) != family_name() )
                return notify_fail("奇门玄术只能桃花岛弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}