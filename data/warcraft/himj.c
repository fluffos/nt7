// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("苛工[2;37;0m[2;37;0m", ({"sdaf"}));        
        set("gender", "男性");                
        set("long", "苛工[2;37;0m
它是一指禅功的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "himj");
        set("owner_name", "一指禅功");
        set_temp("owner", "himj");
        set_temp("owner_name", "一指禅功");
        ::setup();
}
