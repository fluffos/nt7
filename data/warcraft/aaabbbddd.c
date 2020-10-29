// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是少林的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "aaabbbddd");
        set("owner_name", "少林");
        set_temp("owner", "aaabbbddd");
        set_temp("owner_name", "少林");
        ::setup();
}
