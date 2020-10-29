// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("骡子[2;37;0m[2;37;0m", ({"damibb"}));        
        set("gender", "男性");                
        set("long", "gggh[2;37;0m
它是药贩子二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "damib");
        set("owner_name", "药贩子二");
        set_temp("owner", "damib");
        set_temp("owner_name", "药贩子二");
        ::setup();
}
