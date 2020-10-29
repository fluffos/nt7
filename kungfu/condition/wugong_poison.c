// wugong_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "wugong_poison"; }

string chinese_name() { return "蜈蚣毒"; }

string update_msg_others()
{
       return HIG "$N" HIG "的身体一震，神色发散，七窍开始向外流血。" NOR;
}

string update_msg_self()
{
        return HIG "你觉得伤口火辣辣地痛，不禁皱了皱眉头。你中的蜈蚣毒发作了！\n" NOR;
}
