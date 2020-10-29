// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("车车车[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "                [2;37;0m
它是银票的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cash");
        set("owner_name", "银票");
        set_temp("owner", "cash");
        set_temp("owner_name", "银票");
        ::setup();
}
