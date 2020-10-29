// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m玉[2;37;0m[2;37;0m[2;37;0m", ({"jade"}));        
        set("gender", "女性");                
        set("long", "呵呵[2;37;0m
它是北冥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "beiming");
        set("owner_name", "北冥");
        set_temp("owner", "beiming");
        set_temp("owner_name", "北冥");
        ::setup();
}
