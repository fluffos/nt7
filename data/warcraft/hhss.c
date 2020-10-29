// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("灵英[2;37;0m[2;37;0m", ({"jinlong"}));        
        set("gender", "男性");                
        set("long", "异族人[2;37;0m
它是唐烈的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hhss");
        set("owner_name", "唐烈");
        set_temp("owner", "hhss");
        set_temp("owner_name", "唐烈");
        ::setup();
}
