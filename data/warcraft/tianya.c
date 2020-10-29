// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m小毛驴[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "小毛驴[2;37;0m
它是天涯的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tianya");
        set("owner_name", "天涯");
        set_temp("owner", "tianya");
        set_temp("owner_name", "天涯");
        ::setup();
}
