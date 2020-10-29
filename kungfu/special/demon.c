// This program is a part of NITAN MudLIB
// demon.c 万魔附体
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "万魔附体" NOR; }

void remove_effect(object me, int amount);

int perform(object me, string skill)
{
        int n;

        if( query_temp("special_skill/demon", me) )
                return notify_fail("你万魔附体之术已在施展中了。\n");

        message_vision(HIG "$N" HIG "施展出万魔附体之术，刹那间全身真气迸发，犹如蚩尤再现，威猛无比！\n" NOR, me);

        n = me->query_skill("force");
        if (n < 100) n = 100;

        addn_temp("apply/armor", n*3, me);
        addn_temp("apply/reduce_damage", 30, me);
        set_temp("special_skill/demon", 1, me);
 
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, n * 3 :), n/10);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("special_skill/demon", me) )
        {
                addn_temp("apply/armor", -amount, me);
                addn_temp("apply/reduce_damage", -30, me);
                delete_temp("special_skill/demon", me);
                tell_object(me, "你万魔附体之术已施展完毕。\n");
        }
        
}

