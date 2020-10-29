// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"rzjs"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是莽牯朱蛤的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "rzj");
        set("owner_name", "莽牯朱蛤");
        set_temp("owner", "rzj");
        set_temp("owner_name", "莽牯朱蛤");
        ::setup();
}
