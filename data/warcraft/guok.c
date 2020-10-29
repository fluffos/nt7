// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌龟[2;37;0m[2;37;0m", ({"wgui"}));        
        set("gender", "男性");                
        set("long", "乌龟[2;37;0m
它是过客的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "guok");
        set("owner_name", "过客");
        set_temp("owner", "guok");
        set_temp("owner_name", "过客");
        ::setup();
}
