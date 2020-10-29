// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[42m[1;31m渡劫飞升[2;37;0m[2;37;0m", ({"ture"}));        
        set("gender", "男性");                
        set("long", "马上要渡劫飞升仙界，前辈不是你们这些蝼蚁看的。[2;37;0m
它是邵流泪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "swingswing");
        set("owner_name", "邵流泪");
        set_temp("owner", "swingswing");
        set_temp("owner_name", "邵流泪");
        ::setup();
}
