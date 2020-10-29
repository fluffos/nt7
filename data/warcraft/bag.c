// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m暴龙[2;37;0m[2;37;0m", ({"bao"}));        
        set("gender", "男性");                
        set("long", "暴龙[2;37;0m
它是包包的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bag");
        set("owner_name", "包包");
        set_temp("owner", "bag");
        set_temp("owner_name", "包包");
        ::setup();
}
