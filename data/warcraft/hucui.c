// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("关外麒麟[2;37;0m[2;37;0m", ({"hucuiride"}));        
        set("gender", "男性");                
        set("long", "关外麒麟[2;37;0m
它是胡翠的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hucui");
        set("owner_name", "胡翠");
        set_temp("owner", "hucui");
        set_temp("owner_name", "胡翠");
        ::setup();
}
