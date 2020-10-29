#include <ansi.h>
// 华山派 jianyi
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "华山派"; }

int valid_learn(object me)
{        
        if (me->query_skill("zixia-shengong", 1) < 120)
                return notify_fail("你紫霞神功火候不足，无法研习剑意。\n");
        
        if( query("family/family_name", me) != family_name() && query("family/family_name", me) != "华山剑宗" )
                return notify_fail("剑意只能华山派弟子方可研习。\n");

        if (me->query_skill("huashan-sword", 1) < 150)
                return notify_fail("你华山剑法修为不足，无法继续研习剑意。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
