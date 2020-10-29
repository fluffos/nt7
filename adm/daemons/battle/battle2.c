
#include <ansi.h>
void create()
{
        seteuid(getuid());
}

void refresh_map()
{
        object ob;
        
        if( objectp(ob = find_object("/maze/battle2/maze")) )
                destruct(ob);
        if( objectp(ob = find_object("/maze/battle2/enter1")) )
                destruct(ob);
        if( objectp(ob = find_object("/maze/battle2/enter2")) )
                destruct(ob);
}

void init_battle()
{
        if( !find_object(BATTLEFIELD_D) ) return;
        
        refresh_map();
        
        BATTLEFIELD_D->set_battle_name(HIY"王者归来"NOR);
        BATTLEFIELD_D->set_team_name(HIR"王者队"NOR, HIB"无敌队"NOR);
        BATTLEFIELD_D->set_entry_room("/maze/battle2/enter1", "/maze/battle2/enter2");
        BATTLEFIELD_D->set_bonus_percent(120); // 奖励120%
}



