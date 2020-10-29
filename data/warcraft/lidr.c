// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("练了[2;37;0m[2;37;0m", ({"lidra"}));        
        set("gender", "男性");                
        set("long", "练了[2;37;0m
它是炼川的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidr");
        set("owner_name", "炼川");
        set_temp("owner", "lidr");
        set_temp("owner_name", "炼川");
        ::setup();
}
