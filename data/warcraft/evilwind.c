// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m暴[5m[1;36m风[2;37;0m[1;31m狂[5m[1;36m雨[2;37;0m[2;37;0m[2;37;0m", ({"windrain"}));        
        set("gender", "男性");                
        set("long", "狂风暴雨！[2;37;0m
它是风雨飘零的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evilwind");
        set("owner_name", "风雨飘零");
        set_temp("owner", "evilwind");
        set_temp("owner_name", "风雨飘零");
        ::setup();
}
