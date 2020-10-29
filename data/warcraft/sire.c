// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"eris"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是灭惊的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sire");
        set("owner_name", "灭惊");
        set_temp("owner", "sire");
        set_temp("owner_name", "灭惊");
        ::setup();
}
