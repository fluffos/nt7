// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("随意[2;37;0m[2;37;0m", ({"sll"}));        
        set("gender", "男性");                
        set("long", "随便[2;37;0m
它是随风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sleep");
        set("owner_name", "随风");
        set_temp("owner", "sleep");
        set_temp("owner_name", "随风");
        ::setup();
}
