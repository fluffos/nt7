// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("万恶[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "灰白[2;37;0m
它是狂五的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuange");
        set("owner_name", "狂五");
        set_temp("owner", "kuange");
        set_temp("owner_name", "狂五");
        ::setup();
}
