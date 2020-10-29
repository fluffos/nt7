// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("磷矿石定价[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "磷矿石定价[2;37;0m
它是葡萄五号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lye");
        set("owner_name", "葡萄五号");
        set_temp("owner", "lye");
        set_temp("owner_name", "葡萄五号");
        ::setup();
}
