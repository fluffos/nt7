// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("发妈咪[2;37;0m[2;37;0m", ({"fumami"}));        
        set("gender", "女性");                
        set("long", "发妈咪[2;37;0m
它是唐大坑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cescj");
        set("owner_name", "唐大坑");
        set_temp("owner", "cescj");
        set_temp("owner_name", "唐大坑");
        ::setup();
}
