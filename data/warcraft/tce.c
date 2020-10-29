// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qingiv"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是菜农五的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tce");
        set("owner_name", "菜农五");
        set_temp("owner", "tce");
        set_temp("owner_name", "菜农五");
        ::setup();
}
