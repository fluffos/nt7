// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪二八[2;37;0m[2;37;0m", ({"xxl"}));        
        set("gender", "男性");                
        set("long", "猪二八[2;37;0m
它是多多的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xxlowekk");
        set("owner_name", "多多");
        set_temp("owner", "xxlowekk");
        set_temp("owner_name", "多多");
        ::setup();
}
