// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("童子[2;37;0m[2;37;0m", ({"tongzi"}));        
        set("gender", "男性");                
        set("long", "童子[2;37;0m
它是药米的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yaomi");
        set("owner_name", "药米");
        set_temp("owner", "yaomi");
        set_temp("owner_name", "药米");
        ::setup();
}
