// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "            [2;37;0m
它是魔法师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "magic");
        set("owner_name", "魔法师");
        set_temp("owner", "magic");
        set_temp("owner_name", "魔法师");
        ::setup();
}
