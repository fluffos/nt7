// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "女性");                
        set("long", "龙[2;37;0m
它是一堆米的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "simer");
        set("owner_name", "一堆米");
        set_temp("owner", "simer");
        set_temp("owner_name", "一堆米");
        ::setup();
}
