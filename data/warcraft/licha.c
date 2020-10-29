// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("独孤扮猪[2;37;0m[2;37;0m", ({"lichasm"}));        
        set("gender", "男性");                
        set("long", "猪[2;37;0m
它是永生不的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "licha");
        set("owner_name", "永生不");
        set_temp("owner", "licha");
        set_temp("owner_name", "永生不");
        ::setup();
}
