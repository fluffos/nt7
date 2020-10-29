// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("情侣[2;37;0m[2;37;0m", ({"lmm"}));        
        set("gender", "男性");                
        set("long", "情侣[2;37;0m
它是恒九的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zzhg");
        set("owner_name", "恒九");
        set_temp("owner", "zzhg");
        set_temp("owner_name", "恒九");
        ::setup();
}
