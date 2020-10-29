// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m天魔麒麟[2;37;0m[2;37;0m", ({"xixi"}));        
        set("gender", "女性");                
        set("long", "天魔麒麟[2;37;0m
它是元始天魔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ori");
        set("owner_name", "元始天魔");
        set_temp("owner", "ori");
        set_temp("owner_name", "元始天魔");
        ::setup();
}
