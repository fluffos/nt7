// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐上去[2;37;0m[2;37;0m", ({"makezuo"}));        
        set("gender", "女性");                
        set("long", "坐上去[2;37;0m
它是皇太极的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "syliu");
        set("owner_name", "皇太极");
        set_temp("owner", "syliu");
        set_temp("owner_name", "皇太极");
        ::setup();
}
