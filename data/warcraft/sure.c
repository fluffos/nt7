// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"out"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是孔梦的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sure");
        set("owner_name", "孔梦");
        set_temp("owner", "sure");
        set_temp("owner_name", "孔梦");
        ::setup();
}
