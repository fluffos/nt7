// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"xiaoma"}));        
        set("gender", "男性");                
        set("long", "一匹小马[2;37;0m
它是阿若的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "aruo");
        set("owner_name", "阿若");
        set_temp("owner", "aruo");
        set_temp("owner_name", "阿若");
        ::setup();
}
