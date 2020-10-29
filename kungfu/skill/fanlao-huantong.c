#include <ansi.h>
// 灵鹫 fanlao-huantong
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "灵鹫宫"; }

int valid_learn(object me)
{        
        if (me->query_skill("bahuang-gong", 1) < me->query_skill("fanlao-huantong", 1))
                return notify_fail("你八荒六合唯我独尊功火候不足，无法研习返老还童功。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("返老还童功只能灵鹫宫弟子方可研习。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}