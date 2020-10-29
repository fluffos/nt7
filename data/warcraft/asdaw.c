// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m御[1;36m[5m风[1;31m[5m青[1;33m[5m龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是仿佛额的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "asdaw");
        set("owner_name", "仿佛额");
        set_temp("owner", "asdaw");
        set_temp("owner_name", "仿佛额");
        ::setup();
}
