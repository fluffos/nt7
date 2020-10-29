// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("背篓[2;37;0m[2;37;0m", ({"beiluo"}));        
        set("gender", "男性");                
        set("long", "背篓[2;37;0m
它是捡破烂的的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "waiker");
        set("owner_name", "捡破烂的");
        set_temp("owner", "waiker");
        set_temp("owner_name", "捡破烂的");
        ::setup();
}
