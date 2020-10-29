// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m制式巨龙[2;37;0m[2;37;0m", ({"mhands_dragon"}));        
        set("gender", "男性");                
        set("long", "一头军用制式巨龙。[2;37;0m
它是铁掌仓库的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mhands");
        set("owner_name", "铁掌仓库");
        set_temp("owner", "mhands");
        set_temp("owner_name", "铁掌仓库");
        ::setup();
}
