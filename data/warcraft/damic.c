// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("骡子[2;37;0m[2;37;0m", ({"damicc"}));        
        set("gender", "男性");                
        set("long", "dfg[2;37;0m
它是药贩子三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "damic");
        set("owner_name", "药贩子三");
        set_temp("owner", "damic");
        set_temp("owner_name", "药贩子三");
        ::setup();
}
