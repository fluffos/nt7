// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinlong"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是库存甲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "stocka");
        set("owner_name", "库存甲");
        set_temp("owner", "stocka");
        set_temp("owner_name", "库存甲");
        ::setup();
}
