// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("傲丽薇[2;37;0m[2;37;0m", ({"toflying"}));        
        set("gender", "女性");                
        set("long", "傲丽薇[2;37;0m
它是普派的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "pupai");
        set("owner_name", "普派");
        set_temp("owner", "pupai");
        set_temp("owner_name", "普派");
        ::setup();
}
