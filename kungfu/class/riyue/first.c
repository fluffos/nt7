
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("riyue")+"/dongfang");
        set("start_room","/d/heimuya/neishi");
        ::create();
}

string zm_apply()
{
        return ::zm_apply();
}

