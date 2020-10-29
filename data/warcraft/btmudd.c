// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("变兽四[2;37;0m[2;37;0m", ({"btd"}));        
        set("gender", "男性");                
        set("long", "爽[2;37;0m
它是变态米四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btmudd");
        set("owner_name", "变态米四");
        set_temp("owner", "btmudd");
        set_temp("owner_name", "变态米四");
        ::setup();
}
