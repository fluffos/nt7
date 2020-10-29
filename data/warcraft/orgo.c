// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "14234[2;37;0m
它是水仙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "orgo");
        set("owner_name", "水仙");
        set_temp("owner", "orgo");
        set_temp("owner_name", "水仙");
        ::setup();
}
