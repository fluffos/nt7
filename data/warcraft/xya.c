// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m薛[1;33m定[31m谔[1;32m的[34m猫[2;37;0m[2;37;0m", ({"zhuxian"}));        
        set("gender", "男性");                
        set("long", "麻烦[2;37;0m
它是八九玄功的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xya");
        set("owner_name", "八九玄功");
        set_temp("owner", "xya");
        set_temp("owner_name", "八九玄功");
        ::setup();
}
