// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("离开围殴[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "离开围殴[2;37;0m
它是葡萄六号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyf");
        set("owner_name", "葡萄六号");
        set_temp("owner", "lyf");
        set_temp("owner_name", "葡萄六号");
        ::setup();
}
