// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"out"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是灵汆的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cuan");
        set("owner_name", "灵汆");
        set_temp("owner", "cuan");
        set_temp("owner_name", "灵汆");
        ::setup();
}
