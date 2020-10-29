// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("和也让[2;37;0m[2;37;0m", ({"hhads"}));        
        set("gender", "女性");                
        set("long", "和也让[2;37;0m
它是牛刀尖的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "syshi");
        set("owner_name", "牛刀尖");
        set_temp("owner", "syshi");
        set_temp("owner_name", "牛刀尖");
        ::setup();
}
