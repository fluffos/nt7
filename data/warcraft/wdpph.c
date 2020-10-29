// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("都[2;37;0m[2;37;0m", ({"mygift"}));        
        set("gender", "女性");                
        set("long", "都[2;37;0m
它是武当师八的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wdpph");
        set("owner_name", "武当师八");
        set_temp("owner", "wdpph");
        set_temp("owner_name", "武当师八");
        ::setup();
}
