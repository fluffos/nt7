// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"sadas"}));        
        set("gender", "女性");                
        set("long", "dawd1[2;37;0m
它是开心的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hhh");
        set("owner_name", "开心");
        set_temp("owner", "hhh");
        set_temp("owner_name", "开心");
        ::setup();
}
