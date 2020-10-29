// zhuha.c 朱蛤奇缘
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "朱蛤奇缘" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你年轻时因机缘巧合，碰巧服用了万毒至\n"
                           "尊的莽牯朱蛤，从此之后百毒不侵。\n");
}
