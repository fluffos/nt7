#include <ansi.h>
// 欧阳世家 驱蛇
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "欧阳世家"; }

int valid_learn(object me)
{        
        if (me->query_skill("jiuyin-hamagong", 1) < 150)
                return notify_fail("你九阴蛤蟆功火候不足，无法研习驱蛇。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("驱蛇只能欧阳世家弟子方可研习。\n");

        if (me->query_skill("baituo-michuan", 1) < 150)
                return notify_fail("你白驼秘传等级不足，无法继续研习驱蛇。\n");

        if (me->query_skill("training", 1) < 150)
                return notify_fail("你驭兽术等级不足，无法继续研习驱蛇。\n");
        
        return 1;
}

int difficult_level()
{
        return 2000;
}