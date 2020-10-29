// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("湖色[2;37;0m[2;37;0m", ({"tana"}));        
        set("gender", "男性");                
        set("long", "吸[2;37;0m
它是左冷禅的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zuo");
        set("owner_name", "左冷禅");
        set_temp("owner", "zuo");
        set_temp("owner_name", "左冷禅");
        ::setup();
}
