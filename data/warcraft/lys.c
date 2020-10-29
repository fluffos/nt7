// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("几乎都是[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "几乎都是[2;37;0m
它是樱桃酒号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lys");
        set("owner_name", "樱桃酒号");
        set_temp("owner", "lys");
        set_temp("owner_name", "樱桃酒号");
        ::setup();
}
