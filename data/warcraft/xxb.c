// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("清风[2;37;0m[2;37;0m", ({"xxblong"}));        
        set("gender", "男性");                
        set("long", "明月[2;37;0m
它是唐楠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xxb");
        set("owner_name", "唐楠");
        set_temp("owner", "xxb");
        set_temp("owner_name", "唐楠");
        ::setup();
}
