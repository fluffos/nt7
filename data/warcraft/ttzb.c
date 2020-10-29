// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("图[2;37;0m[2;37;0m", ({"ttb"}));        
        set("gender", "男性");                
        set("long", "xx[2;37;0m
它是图二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ttzb");
        set("owner_name", "图二");
        set_temp("owner", "ttzb");
        set_temp("owner_name", "图二");
        ::setup();
}
