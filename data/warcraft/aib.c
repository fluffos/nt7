// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啦啦啦[2;37;0m[2;37;0m", ({"sss"}));        
        set("gender", "男性");                
        set("long", "啦啦啦[2;37;0m
它是阿大的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "aib");
        set("owner_name", "阿大");
        set_temp("owner", "aib");
        set_temp("owner_name", "阿大");
        ::setup();
}
