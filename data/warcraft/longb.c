// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("带我[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "          [2;37;0m
它是龙二的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "longb");
        set("owner_name", "龙二");
        set_temp("owner", "longb");
        set_temp("owner_name", "龙二");
        ::setup();
}
