// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ccuu"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是学由的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ccu");
        set("owner_name", "学由");
        set_temp("owner", "ccu");
        set_temp("owner_name", "学由");
        ::setup();
}
