#include <ansi.h>
// 峨嵋 静心 jingxin
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "峨嵋派"; }

int valid_learn(object me)
{        
        if (me->query_skill("huifeng-jian", 1) < 30)
                return notify_fail("你回风拂柳剑火候不足，无法研习静心。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("静心只能峨嵋派弟子方可研习。\n");

        if (me->query_skill("jingxin", 1) / 2 > me->query_skill("mahayana", 1))
                return notify_fail("你大乘涅磐功等级不足，无法继续研习静心。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}