// zhuha.c 朱蛤奇缘
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "武曲转世" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你在转世时巧遇武曲星投胎转世，借助昊\n"
                                                   "天塔神力，你获取武曲星附体转生，拥有\n"
                                                   "常人没有的武学领悟能力。转生后拥有该\n"
                                                   "技能可以提高所有武学研究速度百分之十，\n"
                                                   "并且打坐、吐呐速度提高百份之五十，汲\n"
                                                   "取实战体会速度提高百分之五十。\n");

}
