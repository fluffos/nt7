// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m肥[1;35m肥[2;37;0m[2;37;0m", ({"panzizi"}));        
        set("gender", "男性");                
        set("long", "一头小肥肥[2;37;0m
它是胖胖的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "panzi");
        set("owner_name", "胖胖");
        set_temp("owner", "panzi");
        set_temp("owner_name", "胖胖");
        ::setup();
}
