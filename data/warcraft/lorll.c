// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("墨麒麟[2;37;0m[2;37;0m", ({"qin"}));        
        set("gender", "男性");                
        set("long", "墨麒麟[2;37;0m
它是上官景龙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lorll");
        set("owner_name", "上官景龙");
        set_temp("owner", "lorll");
        set_temp("owner_name", "上官景龙");
        ::setup();
}
