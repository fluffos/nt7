// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("武海[1;33m[2;37;0m[2;37;0m", ({"taoti"}));        
        set("gender", "女性");                
        set("long", "武海来了[2;37;0m
它是林天河的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "icewater");
        set("owner_name", "林天河");
        set_temp("owner", "icewater");
        set_temp("owner_name", "林天河");
        ::setup();
}
