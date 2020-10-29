// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"fffff"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是翡翠兰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lanx");
        set("owner_name", "翡翠兰");
        set_temp("owner", "lanx");
        set_temp("owner_name", "翡翠兰");
        ::setup();
}
