// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("杂毛龙[2;37;0m[2;37;0m", ({"ookk"}));        
        set("gender", "男性");                
        set("long", "被人天天骑的畜生[2;37;0m
它是赵小婉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zwy");
        set("owner_name", "赵小婉");
        set_temp("owner", "zwy");
        set_temp("owner_name", "赵小婉");
        ::setup();
}
