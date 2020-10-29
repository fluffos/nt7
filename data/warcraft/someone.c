// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("某某某[2;37;0m[2;37;0m", ({"mysomeone"}));        
        set("gender", "男性");                
        set("long", "某某某[2;37;0m
它是某人的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "someone");
        set("owner_name", "某人");
        set_temp("owner", "someone");
        set_temp("owner_name", "某人");
        ::setup();
}
