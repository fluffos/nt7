// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("土土土土土鳖[2;37;0m[2;37;0m", ({"xied"}));        
        set("gender", "男性");                
        set("long", "一只大乌龟[2;37;0m
它是伯赏昆御的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "scdyxied");
        set("owner_name", "伯赏昆御");
        set_temp("owner", "scdyxied");
        set_temp("owner_name", "伯赏昆御");
        ::setup();
}
