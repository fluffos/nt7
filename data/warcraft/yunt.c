// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云飞龙[2;37;0m[2;37;0m", ({"yflong"}));        
        set("gender", "男性");                
        set("long", "云天的飞龙[2;37;0m
它是云天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yunt");
        set("owner_name", "云天");
        set_temp("owner", "yunt");
        set_temp("owner_name", "云天");
        ::setup();
}
