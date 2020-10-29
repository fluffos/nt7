// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宠物[2;37;0m[2;37;0m", ({"cwg"}));        
        set("gender", "女性");                
        set("long", "达到[2;37;0m
它是云飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yfj");
        set("owner_name", "云飞");
        set_temp("owner", "yfj");
        set_temp("owner_name", "云飞");
        ::setup();
}
