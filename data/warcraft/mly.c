// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("饱饱[2;37;0m[2;37;0m", ({"bryan"}));        
        set("gender", "男性");                
        set("long", "我是宝宝。[2;37;0m
它是欧阳春的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mly");
        set("owner_name", "欧阳春");
        set_temp("owner", "mly");
        set_temp("owner_name", "欧阳春");
        ::setup();
}
