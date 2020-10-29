// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("风龙[2;37;0m[2;37;0m", ({"fenglong"}));        
        set("gender", "男性");                
        set("long", "风龙[2;37;0m
它是赤练子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wudan");
        set("owner_name", "赤练子");
        set_temp("owner", "wudan");
        set_temp("owner_name", "赤练子");
        ::setup();
}
