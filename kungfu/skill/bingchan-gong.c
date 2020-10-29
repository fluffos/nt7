#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "星宿派"; }

int valid_learn(object me)
{        
        if (me->query_skill("sanyin-zhua", 1) < 30)
                return notify_fail("你三阴蜈蚣爪火候不足，无法研习冰蚕功。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("冰蚕功只能星宿派弟子方可研习。\n");

        if (me->query_skill("bingchan-gong", 1) / 2 > me->query_skill("xingxiu-qishu", 1)) 
                return notify_fail("你星宿奇术等级不足，无法继续研习冰蚕功。\n"); 

        return 1;
}

int difficult_level()
{
        return 2000;
}