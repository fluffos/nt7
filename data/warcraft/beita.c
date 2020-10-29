// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"xiaoma"}));        
        set("gender", "男性");                
        set("long", "一匹小马[2;37;0m
它是贝塔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "beita");
        set("owner_name", "贝塔");
        set_temp("owner", "beita");
        set_temp("owner_name", "贝塔");
        ::setup();
}
