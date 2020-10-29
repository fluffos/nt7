// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m血玄武[2;37;0m[2;37;0m", ({"kok"}));        
        set("gender", "男性");                
        set("long", "魔兽[2;37;0m
它是血刃的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "crisp");
        set("owner_name", "血刃");
        set_temp("owner", "crisp");
        set_temp("owner_name", "血刃");
        ::setup();
}
