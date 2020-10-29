#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("xuedao")+"/laozu");
        set("start_room","/d/xuedao/shandong3");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        
        if( query("class", ob) != "bonze" )
                return "雪刀门必须是和尚才能担当首席大弟子。\n";
                
        return ::zm_apply();
}
