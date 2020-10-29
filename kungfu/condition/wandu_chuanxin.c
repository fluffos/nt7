#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "qianzhu_wandushou"; }

string chinese_name() { return "穿心剧毒"; }

string update_msg_others()
{
       return HIB "只见$N" HIB "毒气上涌，脸浮现出一层黑气，不住的颤抖。\n" NOR;
}

string update_msg_self()
{
        return HIB "你只觉毒气攻心，头晕目眩，一阵说不出的恶心。\n" NOR;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] * 500;
}