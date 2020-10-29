// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("几乎都是[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "几乎都是[2;37;0m
它是樱桃十号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yjt");
        set("owner_name", "樱桃十号");
        set_temp("owner", "yjt");
        set_temp("owner_name", "樱桃十号");
        ::setup();
}
