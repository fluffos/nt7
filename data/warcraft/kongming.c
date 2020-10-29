// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("佛海[2;37;0m[2;37;0m", ({"kongmingride"}));        
        set("gender", "男性");                
        set("long", "佛海[2;37;0m
它是空名的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kongming");
        set("owner_name", "空名");
        set_temp("owner", "kongming");
        set_temp("owner_name", "空名");
        ::setup();
}
