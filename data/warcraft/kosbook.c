// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("美丽中国梦[2;37;0m[2;37;0m", ({"kosbookpet"}));        
        set("gender", "男性");                
        set("long", "hi[2;37;0m
它是书痴的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosbook");
        set("owner_name", "书痴");
        set_temp("owner", "kosbook");
        set_temp("owner_name", "书痴");
        ::setup();
}
