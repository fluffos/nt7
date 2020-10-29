// zhushang.c 诸伤之术
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "诸伤之术" NOR; }

int perform(object me, string skill)
{
        return notify_fail("此天性者在转世过程中参悟出世间万物生\n"
                           "存之理，能在受伤时驱使万物之灵使对手\n"
                           "也同样受到伤害。\n");
}
