// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("框[2;37;0m[2;37;0m", ({"bang"}));        
        set("gender", "男性");                
        set("long", "框[2;37;0m
它是繁华的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "fan");
        set("owner_name", "繁华");
        set_temp("owner", "fan");
        set_temp("owner_name", "繁华");
        ::setup();
}
