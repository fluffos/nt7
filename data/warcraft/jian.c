// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m剑剑[2;37;0m[2;37;0m", ({"jianjian"}));        
        set("gender", "男性");                
        set("long", "$HIR$剑剑[2;37;0m
它是魔剑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jian");
        set("owner_name", "魔剑");
        set_temp("owner", "jian");
        set_temp("owner_name", "魔剑");
        ::setup();
}
