// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yuetee"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是胡贵的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "btbb");
        set("owner_name", "胡贵");
        set_temp("owner", "btbb");
        set_temp("owner_name", "胡贵");
        ::setup();
}
