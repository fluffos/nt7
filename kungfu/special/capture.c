// This program is a part of NITAN MudLIB
// capture.c 遁影擒踪
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "遁影擒踪" NOR; }

int perform(object me, string skill)
{
        if (me->query_skillo("count", 1) < 8000)
                me->set_skill("count", 8000);

        if (me->query_skillo("mathematics", 1) < 8000)
                me->set_skill("mathematics", 8000);

        return notify_fail("你在转生过程中纵观天象，察觉到了人世间的诸多\n"
                           "奥秘，众生百态尽收眼底。此后不再受到架力卸招\n"                          
                           "之技的迷惑。转生后可得到阴阳八卦及算术八千级。\n"
                           "同时，拥有该技能者可同时施展左右互搏之术，不\n"
                           "再受到阴阳八卦的限制。    \n");
}
