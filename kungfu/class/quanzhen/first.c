#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("quanzhen")+"/wang");
        set("start_room","/d/quanzhen/datang1");
        ::create();
}


string zm_apply()
{
        object ob = this_player();
        if (query("class", ob) != "taoist")
        {
                return "本教例由全真道士掌门！";
        }
        return ::zm_apply();
}
