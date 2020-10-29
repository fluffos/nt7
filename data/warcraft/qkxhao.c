// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"xhaozuoqi"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是拿九阳的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qkxhao");
        set("owner_name", "拿九阳");
        set_temp("owner", "qkxhao");
        set_temp("owner_name", "拿九阳");
        ::setup();
}
