// huanyin_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "huanyin_poison"; }

string chinese_name() { return "幻阴寒毒"; }

string update_msg_others()
{
       return HIG "$N" HIG "的痛苦的呻吟了一声，脸上笼"
              "罩了一股淡淡的绿气。\n" NOR;
}

string update_msg_self()
{
        return HIB "忽然一阵寒气自丹田的而起，逐步渗透到四"
               "肢白赅，透出阵阵寒意。\n" NOR;
}