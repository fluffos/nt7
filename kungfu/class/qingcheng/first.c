
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("qingcheng")+"/yu");
        set("start_room","/d/qingcheng/songfengguan");
        ::create();
}

string zm_apply()
{
        return ::zm_apply();
}
