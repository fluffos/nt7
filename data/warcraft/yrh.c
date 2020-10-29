// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"dsxsss"}));        
        set("gender", "女性");                
        set("long", "多少算术[2;37;0m
它是云儿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yrh");
        set("owner_name", "云儿");
        set_temp("owner", "yrh");
        set_temp("owner_name", "云儿");
        ::setup();
}
