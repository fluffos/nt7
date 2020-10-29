// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "金麒麟[2;37;0m
它是岚斯的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lanshe");
        set("owner_name", "岚斯");
        set_temp("owner", "lanshe");
        set_temp("owner_name", "岚斯");
        ::setup();
}
