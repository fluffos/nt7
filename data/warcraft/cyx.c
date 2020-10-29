// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("念书坐骑[2;37;0m[2;37;0m", ({"cyxzq"}));        
        set("gender", "男性");                
        set("long", "念书坐骑[2;37;0m
它是念书为家的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "cyx");
        set("owner_name", "念书为家");
        set_temp("owner", "cyx");
        set_temp("owner_name", "念书为家");
        ::setup();
}
