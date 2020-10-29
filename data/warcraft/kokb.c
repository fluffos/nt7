// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("很高的[2;37;0m[2;37;0m", ({"kokba"}));        
        set("gender", "男性");                
        set("long", "很高的的地方[2;37;0m
它是敲吧的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kokb");
        set("owner_name", "敲吧");
        set_temp("owner", "kokb");
        set_temp("owner_name", "敲吧");
        ::setup();
}
