// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m九爪[2;37;0m[2;37;0m", ({"jiuzhua"}));        
        set("gender", "男性");                
        set("long", "$MAG$九爪[2;37;0m
它是陌上千绝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "linskx");
        set("owner_name", "陌上千绝");
        set_temp("owner", "linskx");
        set_temp("owner_name", "陌上千绝");
        ::setup();
}
