#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("tangmen")+"/tangltt");
        set("start_room","/d/tangmen/lianyunge");
        ::create();
}

string zm_apply()
{
        return ::zm_apply();
}
