// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是葵花宝典的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "title");
        set("owner_name", "葵花宝典");
        set_temp("owner", "title");
        set_temp("owner_name", "葵花宝典");
        ::setup();
}
