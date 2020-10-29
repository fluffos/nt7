// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小吗[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "              [2;37;0m
它是死洗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sisi");
        set("owner_name", "死洗");
        set_temp("owner", "sisi");
        set_temp("owner_name", "死洗");
        ::setup();
}
