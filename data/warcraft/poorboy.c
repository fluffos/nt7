// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("优良[2;37;0m[2;37;0m", ({"ppbb"}));        
        set("gender", "男性");                
        set("long", "优良[2;37;0m
它是植木的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "poorboy");
        set("owner_name", "植木");
        set_temp("owner", "poorboy");
        set_temp("owner_name", "植木");
        ::setup();
}
