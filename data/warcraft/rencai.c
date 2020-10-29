// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神仙麒麟[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "神仙麒麟[2;37;0m
它是人才的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "rencai");
        set("owner_name", "人才");
        set_temp("owner", "rencai");
        set_temp("owner_name", "人才");
        ::setup();
}
