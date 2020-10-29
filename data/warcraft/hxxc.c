// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"xiaoma"}));        
        set("gender", "男性");                
        set("long", "小马[2;37;0m
它是华默默的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hxxc");
        set("owner_name", "华默默");
        set_temp("owner", "hxxc");
        set_temp("owner_name", "华默默");
        ::setup();
}
