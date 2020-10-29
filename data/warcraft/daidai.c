// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马[2;37;0m[2;37;0m", ({"myma"}));        
        set("gender", "男性");                
        set("long", "一只马[2;37;0m
它是呆呆的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "daidai");
        set("owner_name", "呆呆");
        set_temp("owner", "daidai");
        set_temp("owner_name", "呆呆");
        ::setup();
}
