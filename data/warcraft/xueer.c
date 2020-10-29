// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m雪儿[2;37;0m[2;37;0m", ({"xucer"}));        
        set("gender", "男性");                
        set("long", "独角青龙，好给力哦～[2;37;0m
它是猪九的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xueer");
        set("owner_name", "猪九");
        set_temp("owner", "xueer");
        set_temp("owner_name", "猪九");
        ::setup();
}
