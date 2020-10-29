// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神行者号[2;37;0m[2;37;0m", ({"luhu"}));        
        set("gender", "男性");                
        set("long", "神行者号[2;37;0m
它是唐如的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cove");
        set("owner_name", "唐如");
        set_temp("owner", "cove");
        set_temp("owner_name", "唐如");
        ::setup();
}
