// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("煤炉[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "煤炉[2;37;0m
它是煤球的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mud");
        set("owner_name", "煤球");
        set_temp("owner", "mud");
        set_temp("owner_name", "煤球");
        ::setup();
}
