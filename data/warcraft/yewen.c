// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"yewens"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是烨雯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yewen");
        set("owner_name", "烨雯");
        set_temp("owner", "yewen");
        set_temp("owner_name", "烨雯");
        ::setup();
}
