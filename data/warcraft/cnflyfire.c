// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("附属[2;37;0m[2;37;0m", ({"cncpp"}));        
        set("gender", "男性");                
        set("long", "附属[2;37;0m
它是飞鹰十三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cnflyfire");
        set("owner_name", "飞鹰十三");
        set_temp("owner", "cnflyfire");
        set_temp("owner_name", "飞鹰十三");
        ::setup();
}
