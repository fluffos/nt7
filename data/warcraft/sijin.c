// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("锦似[2;37;0m[2;37;0m", ({"jinsi"}));        
        set("gender", "女性");                
        set("long", "锦似[2;37;0m
它是似锦的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sijin");
        set("owner_name", "似锦");
        set_temp("owner", "sijin");
        set_temp("owner_name", "似锦");
        ::setup();
}
