// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"lidxa"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是星西的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidx");
        set("owner_name", "星西");
        set_temp("owner", "lidx");
        set_temp("owner_name", "星西");
        ::setup();
}
