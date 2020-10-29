// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("风之龙[2;37;0m[2;37;0m", ({"lbin"}));        
        set("gender", "男性");                
        set("long", "这是青龙[2;37;0m
它是风知雪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lbinn");
        set("owner_name", "风知雪");
        set_temp("owner", "lbinn");
        set_temp("owner_name", "风知雪");
        ::setup();
}
