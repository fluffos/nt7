// hatred.c 杀气
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "杀气冲霄" NOR; }

int perform(object me, string skill)
{
        int count;

        if( query("qi", me)<80 )
                return notify_fail("你的体力不支，无法蓄势提升自己的伤害力。\n");

        if( query_temp("special_skill/hatred", me) )
                return notify_fail("你现在已经是杀气腾腾了。\n");

        message_vision(HIR "$N" HIR "眼中精光闪过，冷冷的扫过"
                       "四周，一股寒意凛然而起。\n" NOR, me);
        switch(query("character", me) )
        {
        case "光明磊落":
                count = 30;
                break;

        case "心狠手辣":
                count = 42;
                break;

        case "狡黠多变":
                count = 38;
                break;

        case "阴险奸诈":
                count = 48;
                break;

        case "国士无双":
                count = 60;
                break;

        }

        count *= me->query_str();
        set_temp("special_skill/hatred", 1, me);
        me->receive_damage("qi", 40 + random(40));
        addn_temp("apply/damage", count, me);
        addn_temp("apply/unarmed_damage", count, me);
           me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              count :), 60 + random(30));

        return 1;
}

void remove_effect(object me, int count)
{
        delete_temp("special_skill/hatred", me);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);
        tell_object(me, "你精神一松懈，杀气荡然无存。\n");
}
