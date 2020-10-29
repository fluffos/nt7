
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("hengshan")+"/xian");
        set("start_room","/d/hengshan/square");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if (query("gender", ob) != "女性" || query("class", ob)!= "bonze")
        {
                return "本派只有女尼才能接任掌门弟子一职！";
        }
        return ::zm_apply();
}

