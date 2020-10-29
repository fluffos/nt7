// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是库存辛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "stockh");
        set("owner_name", "库存辛");
        set_temp("owner", "stockh");
        set_temp("owner_name", "库存辛");
        ::setup();
}
