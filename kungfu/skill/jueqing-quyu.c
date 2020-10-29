
#include <ansi.h>
// 古墓派 jueqing-quyu
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "古墓派"; }

int valid_learn(object me)
{       
        if (me->query("family/family_name") != family_name())
                return notify_fail("绝情去欲只能古墓派弟子方可研习。\n");

        if (me->query_skill("yunv-xinjing", 1) < 200)
                return notify_fail("你玉女心经火候不足，无法绝情去欲。\n");

        return 1;
}

int difficult_level()
{
        return 6000;
}

