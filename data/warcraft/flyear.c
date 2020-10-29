// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞龙[2;37;0m[2;37;0m", ({"dra"}));        
        set("gender", "男性");                
        set("long", "飞龙在天[2;37;0m
它是飞韵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "flyear");
        set("owner_name", "飞韵");
        set_temp("owner", "flyear");
        set_temp("owner_name", "飞韵");
        ::setup();
}
