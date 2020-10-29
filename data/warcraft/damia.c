// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("骡子[2;37;0m[2;37;0m", ({"damiaa"}));        
        set("gender", "男性");                
        set("long", "rwer[2;37;0m
它是药贩子一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "damia");
        set("owner_name", "药贩子一");
        set_temp("owner", "damia");
        set_temp("owner_name", "药贩子一");
        ::setup();
}
