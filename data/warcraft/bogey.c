// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m炎龟[2;37;0m[2;37;0m", ({"head"}));        
        set("gender", "男性");                
        set("long", "炎龟一只。[2;37;0m
它是段德的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "bogey");
        set("owner_name", "段德");
        set_temp("owner", "bogey");
        set_temp("owner_name", "段德");
        ::setup();
}
