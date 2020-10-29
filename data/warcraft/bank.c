// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m黄金麒麟[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "——[2;37;0m
它是钱庄的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bank");
        set("owner_name", "钱庄");
        set_temp("owner", "bank");
        set_temp("owner_name", "钱庄");
        ::setup();
}
