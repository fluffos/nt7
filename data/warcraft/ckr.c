// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狴犴[2;37;0m[2;37;0m", ({"bixuan"}));        
        set("gender", "男性");                
        set("long", "狴犴[2;37;0m
它是楚风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ckr");
        set("owner_name", "楚风");
        set_temp("owner", "ckr");
        set_temp("owner_name", "楚风");
        ::setup();
}
