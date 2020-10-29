// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m壹雪[2;37;0m[2;37;0m", ({"matopet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是雪壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mato");
        set("owner_name", "雪壹");
        set_temp("owner", "mato");
        set_temp("owner_name", "雪壹");
        ::setup();
}
