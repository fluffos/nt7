
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("gaibang")+"/hong");
        set("start_room", "/d/gaibang/gbxiaowu");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if ( !query("family/beggarlvl", ob) )
                return "非丐帮有袋弟子，不能胜任掌门弟子一职。";
        return ::zm_apply();
}

