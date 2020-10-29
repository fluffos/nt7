// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"dalong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是头盔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kua");
        set("owner_name", "头盔");
        set_temp("owner", "kua");
        set_temp("owner_name", "头盔");
        ::setup();
}
