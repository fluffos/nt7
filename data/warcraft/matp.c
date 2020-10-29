// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m贰雪[2;37;0m[2;37;0m", ({"matppet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是雪贰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matp");
        set("owner_name", "雪贰");
        set_temp("owner", "matp");
        set_temp("owner_name", "雪贰");
        ::setup();
}
