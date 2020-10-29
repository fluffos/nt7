// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"yek"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是肖月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kay");
        set("owner_name", "肖月");
        set_temp("owner", "kay");
        set_temp("owner_name", "肖月");
        ::setup();
}
