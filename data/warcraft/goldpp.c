// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啪啪啪[2;37;0m[2;37;0m", ({"goldppp"}));        
        set("gender", "男性");                
        set("long", "啪啪啪[2;37;0m
它是金平的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldpp");
        set("owner_name", "金平");
        set_temp("owner", "goldpp");
        set_temp("owner_name", "金平");
        ::setup();
}
