// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神行太保[2;37;0m[2;37;0m", ({"xiaomi"}));        
        set("gender", "男性");                
        set("long", "123[2;37;0m
它是松果的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "com");
        set("owner_name", "松果");
        set_temp("owner", "com");
        set_temp("owner_name", "松果");
        ::setup();
}
