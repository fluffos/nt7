#include <ansi.h>
// 明教 guangming-jing
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "明教"; }

int valid_learn(object me)
{        
        if (me->query_skill("jiuyang-shengong", 1) < 120)
                return notify_fail("你九阳神功火候不足，无法研习大云光明经。\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("大云光明经只能明教弟子方可研习。\n");

        if (me->query_skill("qiankun-danuoyi", 1) < 150)
                return notify_fail("你乾坤大挪移修为不足，无法继续研习大云光明经。\n");

        return 1;
}

void skill_improved(object me)
{
        if (me->query_skill("guangming-jing", 1) >= 500)
        {
                if( !query("mj_gift/str", me) )
                {
                        addn("str", 1, me);
                        set("mj_gift/str", 1, me);
                        tell_object(me, "由于你的大云光明经修炼达到500级，你的先天臂力增加提高了。\n");
                }
        }
}

int difficult_level()
{
        return 2000;
}
