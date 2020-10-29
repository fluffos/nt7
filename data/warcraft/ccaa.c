// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("界龙[2;37;0m[2;37;0m", ({"wujia"}));        
        set("gender", "男性");                
        set("long", "胖胖痴肥[2;37;0m
它是无界的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ccaa");
        set("owner_name", "无界");
        set_temp("owner", "ccaa");
        set_temp("owner_name", "无界");
        ::setup();
}
