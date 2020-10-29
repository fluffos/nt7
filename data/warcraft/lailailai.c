// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("烤箱[2;37;0m[2;37;0m", ({"laihuling"}));        
        set("gender", "女性");                
        set("long", "可以烤出好吃的东西的器具[2;37;0m
它是松饼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lailailai");
        set("owner_name", "松饼");
        set_temp("owner", "lailailai");
        set_temp("owner_name", "松饼");
        ::setup();
}
