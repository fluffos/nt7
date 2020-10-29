// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三大类[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "         [2;37;0m
它是三品武士的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sanpin");
        set("owner_name", "三品武士");
        set_temp("owner", "sanpin");
        set_temp("owner_name", "三品武士");
        ::setup();
}
