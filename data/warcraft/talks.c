// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m麒麟[2;37;0m[2;37;0m", ({"qlin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是落月的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "talks");
        set("owner_name", "落月");
        set_temp("owner", "talks");
        set_temp("owner_name", "落月");
        ::setup();
}
