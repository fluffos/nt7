// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"bris"}));        
        set("gender", "男性");                
        set("long", "安放[2;37;0m
它是天咖的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sird");
        set("owner_name", "天咖");
        set_temp("owner", "sird");
        set_temp("owner_name", "天咖");
        ::setup();
}
