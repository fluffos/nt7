// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m双拐[2;37;0m[2;37;0m", ({"gooo"}));        
        set("gender", "男性");                
        set("long", "$HIW$双拐[2;37;0m
它是渡心的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "voo");
        set("owner_name", "渡心");
        set_temp("owner", "voo");
        set_temp("owner_name", "渡心");
        ::setup();
}
