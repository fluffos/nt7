// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m壹华[2;37;0m[2;37;0m", ({"matfpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是华壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matf");
        set("owner_name", "华壹");
        set_temp("owner", "matf");
        set_temp("owner_name", "华壹");
        ::setup();
}
