// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丑丑[2;37;0m[2;37;0m", ({"maomao"}));        
        set("gender", "女性");                
        set("long", "傻傻的宠物，估计东南西北都分不清楚[2;37;0m
它是独孤剑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "itch");
        set("owner_name", "独孤剑");
        set_temp("owner", "itch");
        set_temp("owner_name", "独孤剑");
        ::setup();
}
