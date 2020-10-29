// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丰满[2;37;0m[2;37;0m", ({"fengman"}));        
        set("gender", "男性");                
        set("long", "丰满[2;37;0m
它是健康的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "denisc");
        set("owner_name", "健康");
        set_temp("owner", "denisc");
        set_temp("owner_name", "健康");
        ::setup();
}
