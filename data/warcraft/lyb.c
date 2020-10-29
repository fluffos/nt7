// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贼王[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "贼王来了[2;37;0m
它是葡萄二号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyb");
        set("owner_name", "葡萄二号");
        set_temp("owner", "lyb");
        set_temp("owner_name", "葡萄二号");
        ::setup();
}
