// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小顽皮[2;37;0m[2;37;0m", ({"xpp"}));        
        set("gender", "男性");                
        set("long", "头大如斗[2;37;0m
它是皮皮的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pipi");
        set("owner_name", "皮皮");
        set_temp("owner", "pipi");
        set_temp("owner_name", "皮皮");
        ::setup();
}
