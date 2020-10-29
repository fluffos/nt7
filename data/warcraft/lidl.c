// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("练放[2;37;0m[2;37;0m", ({"lidll"}));        
        set("gender", "男性");                
        set("long", "练放[2;37;0m
它是炼土的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidl");
        set("owner_name", "炼土");
        set_temp("owner", "lidl");
        set_temp("owner_name", "炼土");
        ::setup();
}
