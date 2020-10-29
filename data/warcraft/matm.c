// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m陆雪[2;37;0m[2;37;0m", ({"matmpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是雪陆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matm");
        set("owner_name", "雪陆");
        set_temp("owner", "matm");
        set_temp("owner_name", "雪陆");
        ::setup();
}
