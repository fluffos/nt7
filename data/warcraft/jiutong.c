// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m小毛驴[2;37;0m[2;37;0m", ({"maolv"}));        
        set("gender", "男性");                
        set("long", "小毛驴[2;37;0m
它是酒童的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jiutong");
        set("owner_name", "酒童");
        set_temp("owner", "jiutong");
        set_temp("owner_name", "酒童");
        ::setup();
}
