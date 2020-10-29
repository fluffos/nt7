// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"dddd"}));        
        set("gender", "男性");                
        set("long", "一头可以飞的麒麟？~[2;37;0m
它是天外天的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "twt");
        set("owner_name", "天外天");
        set_temp("owner", "twt");
        set_temp("owner_name", "天外天");
        ::setup();
}
