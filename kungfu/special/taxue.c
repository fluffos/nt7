// taxue.c 踏雪无痕
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIW "踏雪无痕" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIW "由于掌握了万物变换真谛，能够充分激发体内的潜力，\n"
                               "使自身在忙乱的时候可以有一定几率降低忙乱时间，\n"
                               "综合效果不如左右互搏及腰带镶嵌效果，但是可以和\n"
                               "左右互搏及腰带镶嵌效果兼容。\n"
                               "同时，在研究轻功类技能的时候速度提升50%。\n" NOR);

}
