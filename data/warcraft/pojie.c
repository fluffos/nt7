// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"cwg"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是破姐的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pojie");
        set("owner_name", "破姐");
        set_temp("owner", "pojie");
        set_temp("owner_name", "破姐");
        ::setup();
}
