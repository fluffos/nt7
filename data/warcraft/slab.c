// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"slablong"}));        
        set("gender", "男性");                
        set("long", "浮云[2;37;0m
它是神龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "slab");
        set("owner_name", "神龙");
        set_temp("owner", "slab");
        set_temp("owner_name", "神龙");
        ::setup();
}
