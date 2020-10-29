// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("七宝如意[2;37;0m[2;37;0m", ({"icelice"}));        
        set("gender", "女性");                
        set("long", "  [2;37;0m
它是冰霓裳的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "iceler");
        set("owner_name", "冰霓裳");
        set_temp("owner", "iceler");
        set_temp("owner_name", "冰霓裳");
        ::setup();
}
