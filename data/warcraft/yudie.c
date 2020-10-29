// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m蝶[1;32m恋[1;31m花[2;37;0m[2;37;0m", ({"qlin"}));        
        set("gender", "女性");                
        set("long", "曾经沧海难为水[2;37;0m
它是雨蝶的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yudie");
        set("owner_name", "雨蝶");
        set_temp("owner", "yudie");
        set_temp("owner_name", "雨蝶");
        ::setup();
}
