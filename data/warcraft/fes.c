// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"ddddd"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是泥娃的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fes");
        set("owner_name", "泥娃");
        set_temp("owner", "fes");
        set_temp("owner_name", "泥娃");
        ::setup();
}
