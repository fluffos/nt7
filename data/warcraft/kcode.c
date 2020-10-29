// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m清[2;37;0m[2;37;0m", ({"hell"}));        
        set("gender", "男性");                
        set("long", "清[2;37;0m
它是怪怪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kcode");
        set("owner_name", "怪怪");
        set_temp("owner", "kcode");
        set_temp("owner_name", "怪怪");
        ::setup();
}
