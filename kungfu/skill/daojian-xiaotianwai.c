#include <ansi.h>
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name1() { return "关外胡家"; }
string family_name2() { return "中原苗家"; }

int valid_learn(object me)
{        

        if( query("family/family_name", me) != family_name1() && query("family/family_name", me) != family_name2() )
                return notify_fail("刀剑啸天外只能胡家弟子或苗家弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}