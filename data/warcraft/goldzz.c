// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("整治中[2;37;0m[2;37;0m", ({"goldzzz"}));        
        set("gender", "男性");                
        set("long", "整治中[2;37;0m
它是金真的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldzz");
        set("owner_name", "金真");
        set_temp("owner", "goldzz");
        set_temp("owner_name", "金真");
        ::setup();
}
