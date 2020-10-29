// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小蚯蚓[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "小蚯蚓[2;37;0m
它是穆桂英的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shsjf");
        set("owner_name", "穆桂英");
        set_temp("owner", "shsjf");
        set_temp("owner_name", "穆桂英");
        ::setup();
}
