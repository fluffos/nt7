#include <ansi.h>
// 武当派 tianwei-zhengqi
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "武当派"; }

int valid_learn(object me)
{        
        if( query("shen", me)<1000000 )
                return notify_fail("你行侠仗义的事做得还不够，现在还无法领悟天威正气。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("天威正气只能武当派弟子方可研习。\n");

        if (me->query_skill("taiji-jian", 1) < 150)
                return notify_fail("你太极剑法修为不足，无法继续研习天威正气。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}