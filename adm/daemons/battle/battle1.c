#include <ansi.h>
void create()
{
        seteuid(getuid());
}

void refresh_map()
{
        int i;
        object ob;
        object *dirs;

        dirs = get_dir("/maze/battle1/" + "*.c"); 
        for( i=0; i<sizeof(dirs); i++ )
        {
                ob = find_object("/maze/battle1/" + dirs[i]);
                if( objectp(ob = find_object("/maze/battle1/" + dirs[i])) )
                        destruct(ob);
        }
}

void init_battle()
{
        int level;
        if( !find_object(BATTLEFIELD_D) ) return;
        
        refresh_map();
        
        level = 1000 + random(1000);
        BATTLEFIELD_D->set_battle_name(HIG"谁与争锋"NOR);
        BATTLEFIELD_D->set_team_name(RED"赤火队"NOR, HIB"啸云队"NOR);
        BATTLEFIELD_D->set_entry_room("/maze/battle1/wgate", "/maze/battle1/egate");
        BATTLEFIELD_D->set_bonus_percent(100); // 奖励100%
        set("flag", 1, get_object("/maze/battle1/etang"));
        set("team_name", HIB"啸云队"NOR, get_object("/maze/battle1/etang")); 
        set("team_name", HIB"啸云队"NOR, get_object("/maze/battle1/eting")); 
        set("flag", 1, get_object("/maze/battle1/wtang"));
        set("team_name", RED"赤火队"NOR, get_object("/maze/battle1/wtang")); 
        set("team_name", RED"赤火队"NOR, get_object("/maze/battle1/wting")); 
}


