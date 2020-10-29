// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小飞飞[2;37;0m[2;37;0m", ({"wlms"}));        
        set("gender", "男性");                
        set("long", "=。=[2;37;0m
它是欧阳天宇的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "williams");
        set("owner_name", "欧阳天宇");
        set_temp("owner", "williams");
        set_temp("owner_name", "欧阳天宇");
        ::setup();
}
