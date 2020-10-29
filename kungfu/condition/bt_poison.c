//ice_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bt_poison"; }

string chinese_name() { return "白驼奇毒"; }

string update_msg_others()
{
       return HIB "$N的身子突然晃了两晃，显得很痛苦的样子。\n" NOR;
}

string update_msg_self()
{
        return HIB "忽然一阵刺痛，你感觉毒性正在慢慢侵入你的身体！\n" NOR;
}