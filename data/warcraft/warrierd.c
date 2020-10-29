// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m乌龟[2;37;0m[2;37;0m", ({"help_nick"}));        
        set("gender", "男性");                
        set("long", "只比乌龟厉害那么一点点[2;37;0m
它是达摩的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "warrierd");
        set("owner_name", "达摩");
        set_temp("owner", "warrierd");
        set_temp("owner_name", "达摩");
        ::setup();
}
