// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小子[2;37;0m[2;37;0m", ({"thl"}));        
        set("gender", "女性");                
        set("long", "小子[2;37;0m
它是独孤一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bqa");
        set("owner_name", "独孤一");
        set_temp("owner", "bqa");
        set_temp("owner_name", "独孤一");
        ::setup();
}
