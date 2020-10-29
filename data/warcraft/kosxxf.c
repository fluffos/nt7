// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m陆学[2;37;0m[2;37;0m", ({"kosxxfpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是学陆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosxxf");
        set("owner_name", "学陆");
        set_temp("owner", "kosxxf");
        set_temp("owner_name", "学陆");
        ::setup();
}
