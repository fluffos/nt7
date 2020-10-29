// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小胖胖[2;37;0m[2;37;0m", ({"baipa"}));        
        set("gender", "男性");                
        set("long", "胖胖[2;37;0m
它是深入浅出的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "markcsie");
        set("owner_name", "深入浅出");
        set_temp("owner", "markcsie");
        set_temp("owner_name", "深入浅出");
        ::setup();
}
