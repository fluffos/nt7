// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("变兽一[2;37;0m[2;37;0m", ({"bta"}));        
        set("gender", "男性");                
        set("long", "双[2;37;0m
它是变态米一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btmuda");
        set("owner_name", "变态米一");
        set_temp("owner", "btmuda");
        set_temp("owner_name", "变态米一");
        ::setup();
}
