// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("二小月份[2;37;0m[2;37;0m", ({"febb"}));        
        set("gender", "男性");                
        set("long", "cancel[2;37;0m
它是二月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "feb");
        set("owner_name", "二月");
        set_temp("owner", "feb");
        set_temp("owner_name", "二月");
        ::setup();
}
