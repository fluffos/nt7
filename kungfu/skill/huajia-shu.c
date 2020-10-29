#include <ansi.h>
// 全真化甲术 huajia-shu
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "全真教"; }

int valid_learn(object me)
{        
        if (me->query_skill("quanzhen-jian", 1) < 30)
                return notify_fail("你全真剑法火候不足，无法研习化甲术。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("化甲术只能全真教弟子方可研习。\n");

        if (me->query_skill("taoism", 1) < 
            me->query_skill("huajia-shu", 1) * 60 /100)
                return notify_fail("你道学心发修为不足，无法继续研习化甲术。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
