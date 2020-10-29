// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小强[2;37;0m[2;37;0m", ({"redleaf"}));        
        set("gender", "男性");                
        set("long", "小强[2;37;0m
它是小样儿的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mate");
        set("owner_name", "小样儿");
        set_temp("owner", "mate");
        set_temp("owner_name", "小样儿");
        ::setup();
}
