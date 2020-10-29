// This program is a part of NITAN MudLIB
// ghost.c 六阴鬼脉
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIB "六阴鬼脉" NOR; }

int perform(object me, string skill)
{
        return notify_fail("乃世间千年一遇的特殊经脉，此脉至阴至寒，身俱\n"
                           "此经脉的婴儿常被误诊为寒毒缠身，医而不得其法，\n"
                           "导致幼年夭折。拥此经脉修炼各种内功将事半功倍。\n"
                           "无论男女，均可直接修炼辟邪剑法或是葵花魔功，\n"
                           "无需再作自宫。拥有该技能的人研究任何可以激发\n"
                           "为内功的技能时，研究效率提高50%。 而内力上限\n"
                           "也可提高50%。\n");
}
