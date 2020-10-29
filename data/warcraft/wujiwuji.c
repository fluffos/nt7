// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血煞[2;37;0m[2;37;0m", ({"super"}));        
        set("gender", "男性");                
        set("long", "血煞[2;37;0m
它是无痕华的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wujiwuji");
        set("owner_name", "无痕华");
        set_temp("owner", "wujiwuji");
        set_temp("owner_name", "无痕华");
        ::setup();
}
