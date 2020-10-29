
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("ouyang")+"/ouyangfeng");
        set("start_room","/d/baituo/damen");
        ::create();
}

string zm_apply()
{

        return ::zm_apply();
}

