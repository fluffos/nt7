// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("琪琪[2;37;0m[2;37;0m", ({"qiling"}));        
        set("gender", "男性");                
        set("long", "琪琪[2;37;0m
它是掏浆糊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yuyuz");
        set("owner_name", "掏浆糊");
        set_temp("owner", "yuyuz");
        set_temp("owner_name", "掏浆糊");
        ::setup();
}
