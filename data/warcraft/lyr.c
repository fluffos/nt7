// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("几乎都是[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "几乎都是[2;37;0m
它是樱桃八号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyr");
        set("owner_name", "樱桃八号");
        set_temp("owner", "lyr");
        set_temp("owner_name", "樱桃八号");
        ::setup();
}
