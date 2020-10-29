// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蚯蚓[2;37;0m[2;37;0m", ({"tiansla"}));        
        set("gender", "男性");                
        set("long", "又细又长[2;37;0m
它是天山来的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tiansl");
        set("owner_name", "天山来");
        set_temp("owner", "tiansl");
        set_temp("owner_name", "天山来");
        ::setup();
}
