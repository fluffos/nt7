// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔龙[2;37;0m[2;37;0m", ({"drogn"}));        
        set("gender", "男性");                
        set("long", "魔龙[2;37;0m
它是那年风雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaole");
        set("owner_name", "那年风雨");
        set_temp("owner", "xiaole");
        set_temp("owner_name", "那年风雨");
        ::setup();
}
