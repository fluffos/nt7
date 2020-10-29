// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天猫[2;37;0m[2;37;0m", ({"skycat"}));        
        set("gender", "男性");                
        set("long", "万恶天猫[2;37;0m
它是汗帛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hab");
        set("owner_name", "汗帛");
        set_temp("owner", "hab");
        set_temp("owner_name", "汗帛");
        ::setup();
}
