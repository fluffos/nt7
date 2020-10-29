// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("骡子[2;37;0m[2;37;0m", ({"damiee"}));        
        set("gender", "男性");                
        set("long", "df[2;37;0m
它是药贩子五的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "damie");
        set("owner_name", "药贩子五");
        set_temp("owner", "damie");
        set_temp("owner_name", "药贩子五");
        ::setup();
}
