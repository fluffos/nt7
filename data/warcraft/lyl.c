// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("速度估计回家[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "速度估计回家[2;37;0m
它是樱桃二号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyl");
        set("owner_name", "樱桃二号");
        set_temp("owner", "lyl");
        set_temp("owner_name", "樱桃二号");
        ::setup();
}
