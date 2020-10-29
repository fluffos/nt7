// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m钢铁[2;37;0m[2;37;0m", ({"tank"}));        
        set("gender", "男性");                
        set("long", "装甲[2;37;0m
它是零零二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "agentii");
        set("owner_name", "零零二");
        set_temp("owner", "agentii");
        set_temp("owner_name", "零零二");
        ::setup();
}
