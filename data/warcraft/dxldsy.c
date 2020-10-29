// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火鸟[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "男性");                
        set("long", "这是一只全身燃烧着熊熊烈焰的火鸟！[2;37;0m
它是海盗的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dxldsy");
        set("owner_name", "海盗");
        set_temp("owner", "dxldsy");
        set_temp("owner_name", "海盗");
        ::setup();
}
