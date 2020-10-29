// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("怪物之首[2;37;0m[2;37;0m", ({"iclaaa"}));        
        set("gender", "男性");                
        set("long", "怪物之首啊啊啊啊[2;37;0m
它是洛克废了的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "icl");
        set("owner_name", "洛克废了");
        set_temp("owner", "icl");
        set_temp("owner_name", "洛克废了");
        ::setup();
}
