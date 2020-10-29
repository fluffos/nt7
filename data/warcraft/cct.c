// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"cctt"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是学提的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cct");
        set("owner_name", "学提");
        set_temp("owner", "cct");
        set_temp("owner_name", "学提");
        ::setup();
}
