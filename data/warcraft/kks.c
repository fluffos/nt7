// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小可爱[2;37;0m[2;37;0m", ({"mhs"}));        
        set("gender", "男性");                
        set("long", "小可爱[2;37;0m
它是楚留香的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kks");
        set("owner_name", "楚留香");
        set_temp("owner", "kks");
        set_temp("owner_name", "楚留香");
        ::setup();
}
