// This program is a part of NITAN MudLIB
// nopoison.c 群邪辟易
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "群邪辟易" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你转世时自饿鬼道轮回后所拥有的体质，从此之后\n"
                           "百毒不侵，诸病不染。不但能将七星海棠、断肠花\n"
                           "以及常见的毒素于无形，甚至于吸星大法、乾坤大\n"
                           "挪移之类神功的反噬也能轻易化解。且拥有此体质\n"
                           "的玩家研究和汲取时提升效果50%。\n");
}
