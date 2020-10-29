// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"abookpet"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是墨一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "abook");
        set("owner_name", "墨一");
        set_temp("owner", "abook");
        set_temp("owner_name", "墨一");
        ::setup();
}
