// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("九阳[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "九阳[2;37;0m
它是九阳神功的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cba");
        set("owner_name", "九阳神功");
        set_temp("owner", "cba");
        set_temp("owner_name", "九阳神功");
        ::setup();
}
