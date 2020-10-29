// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("变兽二[2;37;0m[2;37;0m", ({"btb"}));        
        set("gender", "男性");                
        set("long", "爽[2;37;0m
它是变态米二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btmudb");
        set("owner_name", "变态米二");
        set_temp("owner", "btmudb");
        set_temp("owner_name", "变态米二");
        ::setup();
}
