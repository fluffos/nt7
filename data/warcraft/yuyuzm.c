// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巨龙[2;37;0m[2;37;0m", ({"bailong"}));        
        set("gender", "男性");                
        set("long", "巨龙[2;37;0m
它是龙天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yuyuzm");
        set("owner_name", "龙天");
        set_temp("owner", "yuyuzm");
        set_temp("owner_name", "龙天");
        ::setup();
}
