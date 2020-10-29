// This program is a part of NITAN MudLIB
// sophistry.c 诡辩奇学
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "诡辩奇学" NOR; }

int perform(object me, string skill)
{
        return notify_fail("精通诸子百家的各种思想学说，在辨术方面独领风\n"
                           "骚，擅此法者可淆乱是非，点石成金，指鹿为马也\n"
                           "不称奇。任务连续数限制提升一倍，拥有该特技的\n"
                           "玩家在取消师门任务时，当前任务数不归零，且取\n"
                           "消任务不降低江湖威望等相关能力。\n");
}
