// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贼娃子[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "贼娃子来了[2;37;0m
它是葡萄一号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lya");
        set("owner_name", "葡萄一号");
        set_temp("owner", "lya");
        set_temp("owner_name", "葡萄一号");
        ::setup();
}
