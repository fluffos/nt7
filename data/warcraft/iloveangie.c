// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("安琪[2;37;0m[2;37;0m", ({"angie"}));        
        set("gender", "男性");                
        set("long", "快乐的小安琪[2;37;0m
它是独孤惜花的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iloveangie");
        set("owner_name", "独孤惜花");
        set_temp("owner", "iloveangie");
        set_temp("owner_name", "独孤惜花");
        ::setup();
}
