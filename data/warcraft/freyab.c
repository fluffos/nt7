// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("焰群[2;37;0m[2;37;0m", ({"dragoni"}));        
        set("gender", "男性");                
        set("long", "焰群[2;37;0m
它是思凝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "freyab");
        set("owner_name", "思凝");
        set_temp("owner", "freyab");
        set_temp("owner_name", "思凝");
        ::setup();
}
