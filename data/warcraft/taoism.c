// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("九天十地[2;37;0m[2;37;0m", ({"tlong"}));        
        set("gender", "男性");                
        set("long", "沃[2;37;0m
它是水莲道人的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "taoism");
        set("owner_name", "水莲道人");
        set_temp("owner", "taoism");
        set_temp("owner_name", "水莲道人");
        ::setup();
}
