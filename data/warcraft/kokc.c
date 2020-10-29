// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("急急急[2;37;0m[2;37;0m", ({"kokcc"}));        
        set("gender", "男性");                
        set("long", "换个风格[2;37;0m
它是敲嚓的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kokc");
        set("owner_name", "敲嚓");
        set_temp("owner", "kokc");
        set_temp("owner_name", "敲嚓");
        ::setup();
}
