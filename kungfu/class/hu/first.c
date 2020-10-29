#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("hu")+"/hufei");
        set("start_room","/d/guanwai/xiaowu");
        ::create();
}

string zm_apply()
{
        return ::zm_apply();
}
