// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("多达麒麟[2;37;0m[2;37;0m", ({"miduowride"}));        
        set("gender", "男性");                
        set("long", "多达麒麟[2;37;0m
它是米多达的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduolinw");
        set("owner_name", "米多达");
        set_temp("owner", "miduolinw");
        set_temp("owner_name", "米多达");
        ::setup();
}
