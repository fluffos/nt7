// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞猫[2;37;0m[2;37;0m", ({"feitian"}));        
        set("gender", "男性");                
        set("long", "飞猫[2;37;0m
它是烽火连天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fenghuo");
        set("owner_name", "烽火连天");
        set_temp("owner", "fenghuo");
        set_temp("owner_name", "烽火连天");
        ::setup();
}
