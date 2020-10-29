// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宽松的风口[2;37;0m[2;37;0m", ({"fih"}));        
        set("gender", "男性");                
        set("long", "宽松的风口[2;37;0m
它是葡萄八号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yjh");
        set("owner_name", "葡萄八号");
        set_temp("owner", "yjh");
        set_temp("owner_name", "葡萄八号");
        ::setup();
}
