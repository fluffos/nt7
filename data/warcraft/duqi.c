// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火星[2;37;0m[2;37;0m", ({"huoxing"}));        
        set("gender", "男性");                
        set("long", "燃烧的星球[2;37;0m
它是脐带的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "duqi");
        set("owner_name", "脐带");
        set_temp("owner", "duqi");
        set_temp("owner_name", "脐带");
        ::setup();
}
