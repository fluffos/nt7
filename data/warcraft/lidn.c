// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("练草[2;37;0m[2;37;0m", ({"lidna"}));        
        set("gender", "男性");                
        set("long", "练草[2;37;0m
它是炼花的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidn");
        set("owner_name", "炼花");
        set_temp("owner", "lidn");
        set_temp("owner_name", "炼花");
        ::setup();
}
