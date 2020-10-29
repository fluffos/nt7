// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m宝腾莲花[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "$HIR$宝腾莲花[2;37;0m
它是慧电的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jeians");
        set("owner_name", "慧电");
        set_temp("owner", "jeians");
        set_temp("owner_name", "慧电");
        ::setup();
}
