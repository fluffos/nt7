// This program is a part of NITAN MudLIB
// wisdom.c 智周万物
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "智周万物" NOR; }

int perform(object me, string skill)
{
        return notify_fail("由于你在转世的过程中感应到天道的无穷智慧，使\n"
                           "你的学习能力大大提高。拥有该技能者，可提高每\n"
                           "次学习、练习及研究次数上限八百次，学习、练习\n"
                           "及研究效果提升50%。 \n");
}
