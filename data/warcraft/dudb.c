// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("就很好[2;37;0m[2;37;0m", ({"kokl"}));        
        set("gender", "男性");                
        set("long", "会好很多[2;37;0m
它是毒打奔的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dudb");
        set("owner_name", "毒打奔");
        set_temp("owner", "dudb");
        set_temp("owner_name", "毒打奔");
        ::setup();
}
