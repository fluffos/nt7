// guimai.c 六阴鬼脉
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "六阴鬼脉" NOR; }

int perform(object me, string skill)
{
        return notify_fail("乃世间千年一遇的特殊经脉，此脉至阴至\n"
                           "寒，身俱此经脉的婴儿常被误诊为寒毒缠\n"
                           "身，医而不得其法，导致幼年夭折。但若\n"
                           "活过三岁不死者，此后修炼各种内功将事\n"
                           "半功倍，且内力修为比常人更高。无论男\n"
						   "女，均可直接修炼辟邪剑法或是葵花魔功，\n"
						   "无需再作自宫。\n"
						   "注：拥有该技能的人研究任何可以激发为\n"
						   "内功的技能时，研究速度提高10%。而内力\n"
						   "上限也可提高30%。\n");
}