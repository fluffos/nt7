// tianshen.c 真龙天神
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "真龙天神" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIY "炎帝、黄帝、蚩尤同具真龙天神之像，拥有惊天动地\n"
                               "的能力，此能力仅传于嫡系后人。获得此技能者\n"
                               "则完成师门任务后获取任务能力值奖励\n"
                               "提高10%。\n" NOR);


}
