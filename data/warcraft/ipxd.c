// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("名无[2;37;0m[2;37;0m", ({"pop"}));        
        set("gender", "男性");                
        set("long", "啊[2;37;0m
它是丁打杂的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ipxd");
        set("owner_name", "丁打杂");
        set_temp("owner", "ipxd");
        set_temp("owner_name", "丁打杂");
        ::setup();
}
