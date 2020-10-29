// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"longq"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是写特的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shitt");
        set("owner_name", "写特");
        set_temp("owner", "shitt");
        set_temp("owner_name", "写特");
        ::setup();
}
