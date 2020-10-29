// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m维[1;36m他[1;32m命[2;37;0m[2;37;0m[2;37;0m", ({"health"}));        
        set("gender", "女性");                
        set("long", "非常有益健康...^_^[2;37;0m
它是维生素的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "vitamin");
        set("owner_name", "维生素");
        set_temp("owner", "vitamin");
        set_temp("owner_name", "维生素");
        ::setup();
}
