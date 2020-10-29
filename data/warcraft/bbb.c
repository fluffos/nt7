// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m魔幻兽[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "sleep[2;37;0m
它是啊在的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bbb");
        set("owner_name", "啊在");
        set_temp("owner", "bbb");
        set_temp("owner_name", "啊在");
        ::setup();
}
