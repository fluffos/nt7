// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一只青龙[2;37;0m[2;37;0m", ({"dragon"}));        
        set("gender", "男性");                
        set("long", "一只青龙[2;37;0m
它是罗伯特的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "robert");
        set("owner_name", "罗伯特");
        set_temp("owner", "robert");
        set_temp("owner_name", "罗伯特");
        ::setup();
}
