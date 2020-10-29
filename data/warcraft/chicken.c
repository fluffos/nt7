// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙龙七[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "龙龙七[2;37;0m
它是啊大的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chicken");
        set("owner_name", "啊大");
        set_temp("owner", "chicken");
        set_temp("owner_name", "啊大");
        ::setup();
}
