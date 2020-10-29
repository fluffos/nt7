// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m小强[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是华安的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huaan");
        set("owner_name", "华安");
        set_temp("owner", "huaan");
        set_temp("owner_name", "华安");
        ::setup();
}
