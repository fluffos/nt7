// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"dragon_b"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是龙王二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dragonb");
        set("owner_name", "龙王二");
        set_temp("owner", "dragonb");
        set_temp("owner_name", "龙王二");
        ::setup();
}
