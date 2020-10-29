// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("旭日阳刚[2;37;0m[2;37;0m", ({"angel"}));        
        set("gender", "男性");                
        set("long", "旭日阳刚[2;37;0m
它是粽子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zrza");
        set("owner_name", "粽子");
        set_temp("owner", "zrza");
        set_temp("owner_name", "粽子");
        ::setup();
}
