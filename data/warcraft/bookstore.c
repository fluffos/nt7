// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "1123[2;37;0m
它是书童的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bookstore");
        set("owner_name", "书童");
        set_temp("owner", "bookstore");
        set_temp("owner_name", "书童");
        ::setup();
}
