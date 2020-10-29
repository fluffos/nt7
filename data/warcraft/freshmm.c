// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙卡[2;37;0m[2;37;0m", ({"kaka"}));        
        set("gender", "男性");                
        set("long", "别看我[2;37;0m
它是卡卡的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "freshmm");
        set("owner_name", "卡卡");
        set_temp("owner", "freshmm");
        set_temp("owner_name", "卡卡");
        ::setup();
}
