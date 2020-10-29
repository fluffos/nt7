// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "111[2;37;0m
它是吹星星的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nsld");
        set("owner_name", "吹星星");
        set_temp("owner", "nsld");
        set_temp("owner_name", "吹星星");
        ::setup();
}
