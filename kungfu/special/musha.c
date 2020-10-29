// This program is a part of NITAN MudLIB
// musha.c 武星转世
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "武星转世" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你在转世时巧遇武曲星投胎转世，获\n"
                           "取武曲星附体转生，拥有常人没有的\n"
                           "武学领悟能力。转生后拥有该技能可\n"
                           "以提高所有武学研究速度百分之五十，\n"
                           "汲取实战体会速度提高百分之五十。\n");
}
