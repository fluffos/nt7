// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睚眦[2;37;0m[2;37;0m", ({"olo"}));        
        set("gender", "男性");                
        set("long", "龙身鬼口[2;37;0m
它是唐斩的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "opp");
        set("owner_name", "唐斩");
        set_temp("owner", "opp");
        set_temp("owner_name", "唐斩");
        ::setup();
}
