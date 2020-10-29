// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "23456[2;37;0m
它是克莱斯勒的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xzru");
        set("owner_name", "克莱斯勒");
        set_temp("owner", "xzru");
        set_temp("owner_name", "克莱斯勒");
        ::setup();
}
