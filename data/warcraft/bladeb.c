// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("媚儿[2;37;0m[2;37;0m", ({"bladeblong"}));        
        set("gender", "男性");                
        set("long", "焓秦遥[2;37;0m
它是刀疤强的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bladeb");
        set("owner_name", "刀疤强");
        set_temp("owner", "bladeb");
        set_temp("owner_name", "刀疤强");
        ::setup();
}
