// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是独孤少林的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tianhaia");
        set("owner_name", "独孤少林");
        set_temp("owner", "tianhaia");
        set_temp("owner_name", "独孤少林");
        ::setup();
}
