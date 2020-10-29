// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猴[2;37;0m[2;37;0m", ({"goldiii"}));        
        set("gender", "男性");                
        set("long", "猴[2;37;0m
它是金猴的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldii");
        set("owner_name", "金猴");
        set_temp("owner", "goldii");
        set_temp("owner_name", "金猴");
        ::setup();
}
