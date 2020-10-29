// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m火丙[2;37;0m[2;37;0m", ({"matcpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是丙火的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matc");
        set("owner_name", "丙火");
        set_temp("owner", "matc");
        set_temp("owner_name", "丙火");
        ::setup();
}
