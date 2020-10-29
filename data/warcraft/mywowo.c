// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("黑麒麟[2;37;0m[2;37;0m", ({"mywo"}));        
        set("gender", "男性");                
        set("long", "黑麒麟!!![2;37;0m
它是白天只懂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mywowo");
        set("owner_name", "白天只懂");
        set_temp("owner", "mywowo");
        set_temp("owner_name", "白天只懂");
        ::setup();
}
