// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞机[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "飞机[2;37;0m
它是莫名的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hxf");
        set("owner_name", "莫名");
        set_temp("owner", "hxf");
        set_temp("owner_name", "莫名");
        ::setup();
}
