// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("额外好方法[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "额外好方法[2;37;0m
它是樱桃五号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyo");
        set("owner_name", "樱桃五号");
        set_temp("owner", "lyo");
        set_temp("owner_name", "樱桃五号");
        ::setup();
}
