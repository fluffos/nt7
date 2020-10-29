// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("骡子[2;37;0m[2;37;0m", ({"damidd"}));        
        set("gender", "男性");                
        set("long", "fdg[2;37;0m
它是药贩子四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "damid");
        set("owner_name", "药贩子四");
        set_temp("owner", "damid");
        set_temp("owner_name", "药贩子四");
        ::setup();
}
