// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("独孤麒麟[2;37;0m[2;37;0m", ({"jiujianride"}));        
        set("gender", "男性");                
        set("long", "独孤麒麟[2;37;0m
它是许九剑的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jiujian");
        set("owner_name", "许九剑");
        set_temp("owner", "jiujian");
        set_temp("owner_name", "许九剑");
        ::setup();
}
