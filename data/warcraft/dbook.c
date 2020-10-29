// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"dbookpet"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是墨四的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "dbook");
        set("owner_name", "墨四");
        set_temp("owner", "dbook");
        set_temp("owner_name", "墨四");
        ::setup();
}
