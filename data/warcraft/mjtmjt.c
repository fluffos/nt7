// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"mjt"}));        
        set("gender", "男性");                
        set("long", "青龙一只[2;37;0m
它是傲天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mjtmjt");
        set("owner_name", "傲天");
        set_temp("owner", "mjtmjt");
        set_temp("owner_name", "傲天");
        ::setup();
}
