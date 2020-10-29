// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m米其林[2;37;0m[2;37;0m", ({"xxx"}));        
        set("gender", "男性");                
        set("long", "爽[2;37;0m
它是雷根的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "legend");
        set("owner_name", "雷根");
        set_temp("owner", "legend");
        set_temp("owner_name", "雷根");
        ::setup();
}
