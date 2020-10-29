// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m活泼的[2;37;0m[2;37;0m[2;37;0m", ({"louely"}));        
        set("gender", "女性");                
        set("long", "呵呵[2;37;0m
它是耶律枫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zeus");
        set("owner_name", "耶律枫");
        set_temp("owner", "zeus");
        set_temp("owner_name", "耶律枫");
        ::setup();
}
