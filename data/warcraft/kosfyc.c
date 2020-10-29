// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m叁福缘[2;37;0m[2;37;0m", ({"kosfycpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfyc");
        set("owner_name", "福缘叁");
        set_temp("owner", "kosfyc");
        set_temp("owner_name", "福缘叁");
        ::setup();
}
