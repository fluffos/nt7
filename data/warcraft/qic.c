// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xwu"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是弃尘的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "qic");
        set("owner_name", "弃尘");
        set_temp("owner", "qic");
        set_temp("owner_name", "弃尘");
        ::setup();
}
