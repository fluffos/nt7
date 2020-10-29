// tianshen.c 真龙天神
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "真龙天神" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIY "炎帝、黄帝、蚩尤同具真龙天神之像，拥有惊天动地\n"
                               "的能力，此能力仅传于嫡系后人。获得此技能者如为\n"
                               "「真命天子」则完成师门任务后获取任务能力值奖励\n"
                               "提高10%；如为「天煞孤星」则冥思奖励提高10%。\n"
                               "同时，拥有该技能者可不再受限制，可同时拥有真命\n"
                               "天子及天煞孤星两种天性。\n" NOR);


}