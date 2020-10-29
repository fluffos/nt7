// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m麒麟[2;37;0m[2;37;0m", ({"store"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是斯多的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "siduo");
        set("owner_name", "斯多");
        set_temp("owner", "siduo");
        set_temp("owner_name", "斯多");
        ::setup();
}
