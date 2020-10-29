// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ccee"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是学俄的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cce");
        set("owner_name", "学俄");
        set_temp("owner", "cce");
        set_temp("owner_name", "学俄");
        ::setup();
}
