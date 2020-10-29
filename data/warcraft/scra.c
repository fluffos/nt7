// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m芽[2;37;0m[2;37;0m", ({"scar"}));        
        set("gender", "女性");                
        set("long", "精卫填海，永不休止[2;37;0m
它是昱涵的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "scra");
        set("owner_name", "昱涵");
        set_temp("owner", "scra");
        set_temp("owner_name", "昱涵");
        ::setup();
}
