// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m陆福缘[2;37;0m[2;37;0m", ({"kosfyfpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘陆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfyf");
        set("owner_name", "福缘陆");
        set_temp("owner", "kosfyf");
        set_temp("owner_name", "福缘陆");
        ::setup();
}
