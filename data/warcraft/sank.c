// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m高潮汗了[2;37;0m[2;37;0m", ({"xxxx"}));        
        set("gender", "男性");                
        set("long", "，。。。。[2;37;0m
它是玉青山的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sank");
        set("owner_name", "玉青山");
        set_temp("owner", "sank");
        set_temp("owner_name", "玉青山");
        ::setup();
}
