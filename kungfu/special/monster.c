// This program is a part of NITAN MudLIB
// monster.c 天妖临世
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "天妖临世" NOR; }

int perform(object me, string skill)
{
        return notify_fail("此天性者在转世过程中参悟出世间万物生\n"
                           "存之理，能在受伤时驱使万物之灵使对手\n"
                           "也同样受到伤害。\n");
}
