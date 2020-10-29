// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌龟[2;37;0m[2;37;0m", ({"xdf"}));        
        set("gender", "女性");                
        set("long", "小乌龟[2;37;0m
它是独孤三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bqc");
        set("owner_name", "独孤三");
        set_temp("owner", "bqc");
        set_temp("owner_name", "独孤三");
        ::setup();
}
