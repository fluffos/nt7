// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m青龙[2;37;0m[2;37;0m", ({"gdragon"}));        
        set("gender", "男性");                
        set("long", "一条青龙。[2;37;0m
它是武贰狼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "notwo");
        set("owner_name", "武贰狼");
        set_temp("owner", "notwo");
        set_temp("owner_name", "武贰狼");
        ::setup();
}
