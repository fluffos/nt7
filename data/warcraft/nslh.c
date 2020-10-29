// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("晶土建[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "1111[2;37;0m
它是洪荒的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nslh");
        set("owner_name", "洪荒");
        set_temp("owner", "nslh");
        set_temp("owner_name", "洪荒");
        ::setup();
}
