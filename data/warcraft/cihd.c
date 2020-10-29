// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("驴[2;37;0m[2;37;0m", ({"gyill"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是眼四四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cihd");
        set("owner_name", "眼四四");
        set_temp("owner", "cihd");
        set_temp("owner_name", "眼四四");
        ::setup();
}
