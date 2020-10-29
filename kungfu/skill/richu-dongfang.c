#include <ansi.h>
// 日出东方 richu-dongfang
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "日月神教"; }

int valid_learn(object me)
{        
        if (me->query_skill("riyue-jian", 1) < 30)
                return notify_fail("你日月剑法不足，无法研习日出东方。\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("日出东方只能日月神教弟子方可研习。\n");

        if (me->query_skill("riyue-xinfa", 1) < 
            me->query_skill("richu-dongfang", 1) * 60 /100)
                return notify_fail("你日月心法修为不足，无法继续研习日出东方。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
