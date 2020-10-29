// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ffff"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是东海嫡龙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sad");
        set("owner_name", "东海嫡龙");
        set_temp("owner", "sad");
        set_temp("owner_name", "东海嫡龙");
        ::setup();
}
