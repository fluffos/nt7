// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("混沌[2;37;0m[2;37;0m", ({"hundun"}));        
        set("gender", "男性");                
        set("long", "混沌[2;37;0m
它是藏海的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lukx");
        set("owner_name", "藏海");
        set_temp("owner", "lukx");
        set_temp("owner_name", "藏海");
        ::setup();
}
