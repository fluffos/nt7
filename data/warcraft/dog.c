// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m麒麟[5m[2;37;0m[2;37;0m", ({"xdog"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是狗狗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dog");
        set("owner_name", "狗狗");
        set_temp("owner", "dog");
        set_temp("owner_name", "狗狗");
        ::setup();
}
