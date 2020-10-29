// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("低调[2;37;0m[2;37;0m", ({"auxf"}));        
        set("gender", "女性");                
        set("long", "非常的。。。低调[2;37;0m
它是烫爬追魂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "csj");
        set("owner_name", "烫爬追魂");
        set_temp("owner", "csj");
        set_temp("owner_name", "烫爬追魂");
        ::setup();
}
