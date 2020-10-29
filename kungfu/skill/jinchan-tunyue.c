#include <ansi.h>
// 金蟾吞月 jinchan-tunyue
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "欧阳世家"; }

int valid_learn(object me)
{        
        if (me->query_skill("hamagong", 1) < 30)
                return notify_fail("你蛤蟆功火候不足，无法研习金蟾吞月。\n"); 
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("金蟾吞月只能欧阳世家弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
