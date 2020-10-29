// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m土地[2;37;0m[2;37;0m[2;37;0m", ({"tudi"}));        
        set("gender", "男性");                
        set("long", "土地[2;37;0m
它是木逸之的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "droller");
        set("owner_name", "木逸之");
        set_temp("owner", "droller");
        set_temp("owner_name", "木逸之");
        ::setup();
}
