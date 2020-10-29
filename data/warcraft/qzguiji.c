// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("摩托[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "motuoc[2;37;0m
它是天先猛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qzguiji");
        set("owner_name", "天先猛");
        set_temp("owner", "qzguiji");
        set_temp("owner_name", "天先猛");
        ::setup();
}
