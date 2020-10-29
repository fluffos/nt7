// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是张道陵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tdcode");
        set("owner_name", "张道陵");
        set_temp("owner", "tdcode");
        set_temp("owner_name", "张道陵");
        ::setup();
}
