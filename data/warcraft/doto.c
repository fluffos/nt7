// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("漂[2;37;0m[2;37;0m", ({"high"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是莫云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "doto");
        set("owner_name", "莫云");
        set_temp("owner", "doto");
        set_temp("owner_name", "莫云");
        ::setup();
}
