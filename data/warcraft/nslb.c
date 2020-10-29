// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "hi[2;37;0m
它是吹牛逼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "nslb");
        set("owner_name", "吹牛逼");
        set_temp("owner", "nslb");
        set_temp("owner_name", "吹牛逼");
        ::setup();
}
