// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[43;1m[34m天宇[2;37;0m[2;37;0m", ({"tianyu"}));        
        set("gender", "男性");                
        set("long", "天宇[2;37;0m
它是啊发的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "afar");
        set("owner_name", "啊发");
        set_temp("owner", "afar");
        set_temp("owner_name", "啊发");
        ::setup();
}
