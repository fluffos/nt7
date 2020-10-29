// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m标致[1;37m敞篷[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这款标致敞篷为最新款概念车，车震利器、泡妞必备。[2;37;0m
它是洪金宝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "starh");
        set("owner_name", "洪金宝");
        set_temp("owner", "starh");
        set_temp("owner_name", "洪金宝");
        ::setup();
}
