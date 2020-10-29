// might.c 狂暴铁拳
// Created by Vin 25/5/2002

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "狂暴之力" NOR; }

int perform(object me, string skill)
{
        return notify_fail("此乃自远古流传至今的一条稀有血脉，现存于世也不过寥寥无几。据\n"
                           "传拥有此血脉者往往身强体壮，力大无穷。拥有狂暴血脉之人，可以\n"
                           "使其的加力上限提高20%。\n");
}

