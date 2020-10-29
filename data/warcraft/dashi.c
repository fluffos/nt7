// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m小[1;35m沙[1;32m弥[2;37;0m[2;37;0m", ({"shami"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIC$小$HIM$沙$HIG$弥[2;37;0m
它是一灯大师的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dashi");
        set("owner_name", "一灯大师");
        set_temp("owner", "dashi");
        set_temp("owner_name", "一灯大师");
        ::setup();
}
