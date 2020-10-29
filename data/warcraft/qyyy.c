// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("霸下[2;37;0m[2;37;0m", ({"baxia"}));        
        set("gender", "男性");                
        set("long", "古龙之子[2;37;0m
它是青阳一一的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "qyyy");
        set("owner_name", "青阳一一");
        set_temp("owner", "qyyy");
        set_temp("owner_name", "青阳一一");
        ::setup();
}
