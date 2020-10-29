// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"ddddd"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是何和和的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fej");
        set("owner_name", "何和和");
        set_temp("owner", "fej");
        set_temp("owner_name", "何和和");
        ::setup();
}
