// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是凌翎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zbk");
        set("owner_name", "凌翎");
        set_temp("owner", "zbk");
        set_temp("owner_name", "凌翎");
        ::setup();
}
