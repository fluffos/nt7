// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("太古凶兽[2;37;0m[2;37;0m", ({"clothblong"}));        
        set("gender", "男性");                
        set("long", "电脑[2;37;0m
它是甲无码的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "armora");
        set("owner_name", "甲无码");
        set_temp("owner", "armora");
        set_temp("owner_name", "甲无码");
        ::setup();
}
