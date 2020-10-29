// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m扫帚[2;37;0m[2;37;0m", ({"dragon"}));        
        set("gender", "女性");                
        set("long", "`(*∩_∩*)′[2;37;0m
它是唐诗诗的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tangss");
        set("owner_name", "唐诗诗");
        set_temp("owner", "tangss");
        set_temp("owner_name", "唐诗诗");
        ::setup();
}
