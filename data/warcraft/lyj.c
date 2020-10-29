// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("看来是那个[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "看来是那个[2;37;0m
它是葡萄十号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyj");
        set("owner_name", "葡萄十号");
        set_temp("owner", "lyj");
        set_temp("owner_name", "葡萄十号");
        ::setup();
}
