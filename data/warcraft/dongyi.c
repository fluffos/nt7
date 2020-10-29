// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("东[2;37;0m[2;37;0m", ({"wujiu"}));        
        set("gender", "男性");                
        set("long", "东[2;37;0m
它是东夷巫救的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dongyi");
        set("owner_name", "东夷巫救");
        set_temp("owner", "dongyi");
        set_temp("owner_name", "东夷巫救");
        ::setup();
}
