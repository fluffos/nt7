// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("镇定[2;37;0m[2;37;0m", ({"dinghui"}));        
        set("gender", "男性");                
        set("long", "镇定[2;37;0m
它是定慧的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "denisb");
        set("owner_name", "定慧");
        set_temp("owner", "denisb");
        set_temp("owner_name", "定慧");
        ::setup();
}
