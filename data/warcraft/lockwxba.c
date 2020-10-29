// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("竹扫帚[2;37;0m[2;37;0m", ({"saozhou"}));        
        set("gender", "男性");                
        set("long", "一把破旧的竹扫帚。[2;37;0m
它是老仆人的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lockwxba");
        set("owner_name", "老仆人");
        set_temp("owner", "lockwxba");
        set_temp("owner_name", "老仆人");
        ::setup();
}
