// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雷灵兽[2;37;0m[2;37;0m", ({"leilingshou"}));        
        set("gender", "男性");                
        set("long", "天地雷精所化[2;37;0m
它是林镇坤的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zhenkun");
        set("owner_name", "林镇坤");
        set_temp("owner", "zhenkun");
        set_temp("owner_name", "林镇坤");
        ::setup();
}
