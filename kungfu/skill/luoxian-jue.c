#include <ansi.h>
// 落仙诀
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "唐门世家"; }

int valid_learn(object me)
{        
        if (me->query_skill("tangmen-throwing", 1) < 30)
                return notify_fail("你唐门暗器火候不足，无法研习落仙诀。\n"); 
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("落仙诀只能唐门世家弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
