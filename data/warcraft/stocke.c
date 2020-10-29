// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是库存戊的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "stocke");
        set("owner_name", "库存戊");
        set_temp("owner", "stocke");
        set_temp("owner_name", "库存戊");
        ::setup();
}
