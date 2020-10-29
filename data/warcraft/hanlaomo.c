// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("苍兽[2;37;0m[2;37;0m", ({"shenlong"}));        
        set("gender", "男性");                
        set("long", "如苍如荒如太如古[2;37;0m
它是谷君的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hanlaomo");
        set("owner_name", "谷君");
        set_temp("owner", "hanlaomo");
        set_temp("owner_name", "谷君");
        ::setup();
}
