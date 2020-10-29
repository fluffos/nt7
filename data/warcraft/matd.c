// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m火丁[2;37;0m[2;37;0m", ({"matdpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是丁火的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matd");
        set("owner_name", "丁火");
        set_temp("owner", "matd");
        set_temp("owner_name", "丁火");
        ::setup();
}
