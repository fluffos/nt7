// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m青龙牙[2;37;0m[2;37;0m", ({"maburahoaa"}));        
        set("gender", "男性");                
        set("long", "$HIM$青龙牙[2;37;0m
它是阳光的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "maburahoa");
        set("owner_name", "阳光");
        set_temp("owner", "maburahoa");
        set_temp("owner_name", "阳光");
        ::setup();
}
