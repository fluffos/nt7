// hua_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "hua_poison"; }

string chinese_name() { return "化毒"; }

string update_msg_others()
{
       return HIG "$N" HIG "的目光散乱，神色异常，脸上泛出一层黑气。\n" NOR;
}

string update_msg_self()
{
        return HIB "忽然肺腑一阵剧痛，你体内的毒力发作了！\n" NOR;
}
