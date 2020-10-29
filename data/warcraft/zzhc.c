// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"lypp"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是恒三的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zzhc");
        set("owner_name", "恒三");
        set_temp("owner", "zzhc");
        set_temp("owner_name", "恒三");
        ::setup();
}
