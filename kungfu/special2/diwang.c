// diwang.c 帝王之星
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "帝王之星" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIM "此天性者拥有帝王之像，四项先天属性可永久各加两\n"
                               "点。同时，内力上限和精力上限各提升20%， 气血恢\n"
                               "复速度提升30%。\n" NOR);

}