// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("勇气宝宝[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "勇气宝宝[2;37;0m
它是敦皇的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gsj");
        set("owner_name", "敦皇");
        set_temp("owner", "gsj");
        set_temp("owner_name", "敦皇");
        ::setup();
}
