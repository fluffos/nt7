// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m叁华[2;37;0m[2;37;0m", ({"matspet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是华叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mats");
        set("owner_name", "华叁");
        set_temp("owner", "mats");
        set_temp("owner_name", "华叁");
        ::setup();
}
