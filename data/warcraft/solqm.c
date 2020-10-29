// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("随例题[2;37;0m[2;37;0m", ({"qmaaa"}));        
        set("gender", "男性");                
        set("long", "随例题[2;37;0m
它是完美用户的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "solqm");
        set("owner_name", "完美用户");
        set_temp("owner", "solqm");
        set_temp("owner_name", "完美用户");
        ::setup();
}
