// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"hell"}));        
        set("gender", "女性");                
        set("long", "龙[2;37;0m
它是江南一剑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zhai");
        set("owner_name", "江南一剑");
        set_temp("owner", "zhai");
        set_temp("owner_name", "江南一剑");
        ::setup();
}
