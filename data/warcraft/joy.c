// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"fog"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是天邪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "joy");
        set("owner_name", "天邪");
        set_temp("owner", "joy");
        set_temp("owner_name", "天邪");
        ::setup();
}
