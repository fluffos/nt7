// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血莲[2;37;0m[2;37;0m", ({"darkness"}));        
        set("gender", "女性");                
        set("long", "血莲[2;37;0m
它是混沌幻影的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "saberalter");
        set("owner_name", "混沌幻影");
        set_temp("owner", "saberalter");
        set_temp("owner_name", "混沌幻影");
        ::setup();
}
