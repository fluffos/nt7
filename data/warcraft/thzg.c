// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽兽[2;37;0m[2;37;0m", ({"sshou"}));        
        set("gender", "男性");                
        set("long", "兽兽[2;37;0m
它是长工己的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "thzg");
        set("owner_name", "长工己");
        set_temp("owner", "thzg");
        set_temp("owner_name", "长工己");
        ::setup();
}
