// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("紫电[2;37;0m[2;37;0m", ({"zidian"}));        
        set("gender", "男性");                
        set("long", "独一无二[2;37;0m
它是典围的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dian");
        set("owner_name", "典围");
        set_temp("owner", "dian");
        set_temp("owner_name", "典围");
        ::setup();
}
