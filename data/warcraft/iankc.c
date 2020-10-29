// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丰[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "丰[2;37;0m
它是二风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iankc");
        set("owner_name", "二风");
        set_temp("owner", "iankc");
        set_temp("owner_name", "二风");
        ::setup();
}
