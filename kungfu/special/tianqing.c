// guimai.c 天擎秘气
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "天擎秘气" NOR; }

int perform(object me, string skill)
{
        return notify_fail("参破宇宙奥妙，窥视武道至高境界的运功法门，不需要施展，可增加内力和精力上限5%\n");
}

