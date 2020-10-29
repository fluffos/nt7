// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"idb"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是钱梦的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "aidb");
        set("owner_name", "钱梦");
        set_temp("owner", "aidb");
        set_temp("owner_name", "钱梦");
        ::setup();
}
