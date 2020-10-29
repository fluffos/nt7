// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m菊花[2;37;0m[2;37;0m", ({"juhua"}));        
        set("gender", "男性");                
        set("long", "攻防转换契合点[2;37;0m
它是丐爱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gay");
        set("owner_name", "丐爱");
        set_temp("owner", "gay");
        set_temp("owner_name", "丐爱");
        ::setup();
}
