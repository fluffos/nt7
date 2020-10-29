// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("背学[2;37;0m[2;37;0m", ({"beibei"}));        
        set("gender", "男性");                
        set("long", "背学[2;37;0m
它是血战到底的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bei");
        set("owner_name", "血战到底");
        set_temp("owner", "bei");
        set_temp("owner_name", "血战到底");
        ::setup();
}
