// jinghua.c 仙音菁华
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "仙音净化" NOR; }

int perform(object me, string skill)
{
        return notify_fail("在转生的过程中你受到了天界仙音的净化，\n"
                           "转世后自身的先天得到了极大的提升。此\n"
                           "项技能可以使你的先天悟性、根骨、臂力\n"
                           "以及先天身法破格提升两点。\n");

}
