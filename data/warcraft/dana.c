// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"dalong"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是丹大的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dana");
        set("owner_name", "丹大");
        set_temp("owner", "dana");
        set_temp("owner_name", "丹大");
        ::setup();
}
