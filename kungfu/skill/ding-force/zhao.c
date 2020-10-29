//Cracked by Roath
// zhao.c for ding-force
// 金钟罩

#include <ansi.h>

int exert(object me, object target)
{
        int lv, dur, drop;
        string str;
        object ob;

        if( !me->is_fighting() )
                return notify_fail("等跟人打架时再用吧！\n");
        if( query_temp("huti", me) )
                return notify_fail("你已经运起金钟罩护体功了。\n");

        lv = (int)me->query_skill("ding-force", 1);
        dur=query("neili", me);

        if (lv > 150)
        {
                drop = 200 * 150 / lv;
                dur = (dur - drop)/drop;
                str = HIR + me->name() + "骑马蹲裆，气存丹田，暴喝一声：来！\n"
                + HIG + "一道金光飞来，半空中突然落下一只黄金大钟把" +
                me->name() + "罩在里面。\n" + NOR;
        }
        if (dur < 1)
                return notify_fail("你的内力不够运用金钟罩。\n");

        seteuid(geteuid(me));
       
        addn("neili", -drop, me);
        me->apply_condition("zhao", dur);
        set_temp("huti", 1, me);
        write(HIG + "你运起金钟罩护体功。\n" + NOR);
        message("vision", str, environment(me), me);
        return 1;
}
