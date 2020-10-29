// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "小[2;37;0m
它是星火的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "star");
        set("owner_name", "星火");
        set_temp("owner", "star");
        set_temp("owner_name", "星火");
        ::setup();
}
