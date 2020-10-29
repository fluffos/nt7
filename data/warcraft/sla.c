// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m天地一号[2;37;0m[2;37;0m", ({"nitan"}));        
        set("gender", "男性");                
        set("long", "规定[2;37;0m
它是色空的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sla");
        set("owner_name", "色空");
        set_temp("owner", "sla");
        set_temp("owner_name", "色空");
        ::setup();
}
