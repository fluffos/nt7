// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("终生之盟友[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "终生之盟友[2;37;0m
它是试烟的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wwxx");
        set("owner_name", "试烟");
        set_temp("owner", "wwxx");
        set_temp("owner_name", "试烟");
        ::setup();
}
