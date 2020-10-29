// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("禽兽[2;37;0m[2;37;0m", ({"aot"}));        
        set("gender", "男性");                
        set("long", "老虎[2;37;0m
它是大唐药丸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tyao");
        set("owner_name", "大唐药丸");
        set_temp("owner", "tyao");
        set_temp("owner_name", "大唐药丸");
        ::setup();
}
