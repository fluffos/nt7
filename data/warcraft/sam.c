// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞絮[2;37;0m[2;37;0m", ({"sams"}));        
        set("gender", "男性");                
        set("long", "飞絮飘飘[2;37;0m
它是枫龙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sam");
        set("owner_name", "枫龙");
        set_temp("owner", "sam");
        set_temp("owner_name", "枫龙");
        ::setup();
}
