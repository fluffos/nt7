// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("清龙[2;37;0m[2;37;0m", ({"xxelong"}));        
        set("gender", "男性");                
        set("long", "他他[2;37;0m
它是丁二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xxe");
        set("owner_name", "丁二");
        set_temp("owner", "xxe");
        set_temp("owner_name", "丁二");
        ::setup();
}
