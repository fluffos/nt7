// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小青龙[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "男性");                
        set("long", "这是一只青龙幼崽[2;37;0m
它是铁锤的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dsydxl");
        set("owner_name", "铁锤");
        set_temp("owner", "dsydxl");
        set_temp("owner_name", "铁锤");
        ::setup();
}
