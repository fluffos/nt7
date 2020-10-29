// hui.c 蛤蟆功回息

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int n;
        string msg;

        if( !(n=query_temp("reverse", me)) )
                return notify_fail("你并没有倒转经脉啊。\n");

        msg = HIB "$N" HIB "缓缓吐出一口气，脸色变了变，阴阳不定。\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/defense", -n, me);
        addn_temp("apply/armor", -n*2, me);
        addn_temp("apply/dispel_poison", -(n*2+30), me);
        addn_temp("apply/reduce_poison", -10, me);
        delete_temp("reverse", me);

        //set("neili", 0, me);
        return 1;
}
