// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("路过[2;37;0m[2;37;0m", ({"jiji"}));        
        set("gender", "男性");                
        set("long", "路过[2;37;0m
它是卡卡罗特的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kklt");
        set("owner_name", "卡卡罗特");
        set_temp("owner", "kklt");
        set_temp("owner_name", "卡卡罗特");
        ::setup();
}
