// baituo_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "baituo_poison"; }

string chinese_name() { return "白驼蛇毒"; }

string update_msg_others()
{
        return HIR "$N" HIR "一声惨嚎，全身犹如万射齐噬，痛苦不堪。\n" NOR;
}

string update_msg_self()
{
        return HIR "你只觉全身奇痛无比，难以忍受。\n" NOR;
}

string die_msg_others()
{
        return HIR "$N" HIR "焦枯的身子在地上扑腾了几下，就再没"
               "半点动静了。\n" NOR;
}

string die_reason()
{
        return "被白驼蛇毒攻心而死";
}