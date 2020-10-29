// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("紫萱[2;37;0m[2;37;0m", ({"zixuan"}));        
        set("gender", "女性");                
        set("long", "强大的家伙[2;37;0m
它是萱萱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xuanxuan");
        set("owner_name", "萱萱");
        set_temp("owner", "xuanxuan");
        set_temp("owner_name", "萱萱");
        ::setup();
}
