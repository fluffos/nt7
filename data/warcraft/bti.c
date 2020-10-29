// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("娜可露露[2;37;0m[2;37;0m", ({"omo"}));        
        set("gender", "女性");                
        set("long", "没有[2;37;0m
它是周仓四的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bti");
        set("owner_name", "周仓四");
        set_temp("owner", "bti");
        set_temp("owner_name", "周仓四");
        ::setup();
}
