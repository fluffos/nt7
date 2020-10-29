// zhuque.c 朱雀重生
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIR "朱雀重生" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIR "获得烈火凤凰般的体魄， 死亡后有40%几率不损失技\n"
                           "能并且在晕倒的时候有50% 几率获得体内潜力的瞬间爆发，\n"
                           "气血及精力可瞬间自动恢复60%，躲避晕倒，特别在战斗中\n"
                           "可降低因为晕倒而死亡的可能。（如打通生死玄关后死亡不\n"
                           "丢失技能的几率将根据生死玄关的效果累积）\n" NOR);
}