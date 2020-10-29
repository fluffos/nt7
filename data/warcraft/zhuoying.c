// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("捕风[2;37;0m[2;37;0m", ({"bufeng"}));        
        set("gender", "男性");                
        set("long", "捕风[2;37;0m
它是捕风捉影的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zhuoying");
        set("owner_name", "捕风捉影");
        set_temp("owner", "zhuoying");
        set_temp("owner_name", "捕风捉影");
        ::setup();
}
