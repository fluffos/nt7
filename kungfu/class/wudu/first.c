#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("wudu")+"/hetieshou");
        set("start_room","/d/wudu/dating");
        ::create();
}

string zm_apply()
{
        return ::zm_apply();
}
