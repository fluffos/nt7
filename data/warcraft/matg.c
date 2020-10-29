// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m贰华[2;37;0m[2;37;0m", ({"matgpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是华贰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matg");
        set("owner_name", "华贰");
        set_temp("owner", "matg");
        set_temp("owner_name", "华贰");
        ::setup();
}
