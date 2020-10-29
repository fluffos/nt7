#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("mojiao")+"/dingpeng");
        set("start_room","/d/yuanyue/gu3");
        ::create();
}

string zm_apply()
{
        return ::zm_apply();
}