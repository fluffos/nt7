// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神龙[2;37;0m[2;37;0m", ({"shenlong"}));        
        set("gender", "男性");                
        set("long", "天生勇士[2;37;0m
它是唐安琪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tanqi");
        set("owner_name", "唐安琪");
        set_temp("owner", "tanqi");
        set_temp("owner_name", "唐安琪");
        ::setup();
}
