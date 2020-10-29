// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白马王子[2;37;0m[2;37;0m", ({"girlioi"}));        
        set("gender", "女性");                
        set("long", "白马王子[2;37;0m
它是白雪公主的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shkk");
        set("owner_name", "白雪公主");
        set_temp("owner", "shkk");
        set_temp("owner_name", "白雪公主");
        ::setup();
}
