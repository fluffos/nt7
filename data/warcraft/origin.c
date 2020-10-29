// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m天武麒麟[2;37;0m[2;37;0m", ({"ori"}));        
        set("gender", "男性");                
        set("long", "元始天尊座下天武麒麟圣兽。[2;37;0m
它是元始天尊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "origin");
        set("owner_name", "元始天尊");
        set_temp("owner", "origin");
        set_temp("owner_name", "元始天尊");
        ::setup();
}
