// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽兽[2;37;0m[2;37;0m", ({"shoua"}));        
        set("gender", "男性");                
        set("long", "这是兽首[2;37;0m
它是飞为的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "tanga");
        set("owner_name", "飞为");
        set_temp("owner", "tanga");
        set_temp("owner_name", "飞为");
        ::setup();
}
