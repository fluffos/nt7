// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是超人的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "superman");
        set("owner_name", "超人");
        set_temp("owner", "superman");
        set_temp("owner_name", "超人");
        ::setup();
}
