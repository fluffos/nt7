// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("钱钱[2;37;0m[2;37;0m", ({"moneyb"}));        
        set("gender", "男性");                
        set("long", "钱钱[2;37;0m
它是钱二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldb");
        set("owner_name", "钱二");
        set_temp("owner", "goldb");
        set_temp("owner_name", "钱二");
        ::setup();
}
