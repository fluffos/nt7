// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"lql"}));        
        set("gender", "男性");                
        set("long", "天地之子[2;37;0m
它是天莫邪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tmx");
        set("owner_name", "天莫邪");
        set_temp("owner", "tmx");
        set_temp("owner_name", "天莫邪");
        ::setup();
}
