// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"tttt"}));        
        set("gender", "男性");                
        set("long", "                      [2;37;0m
它是地堤的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "titi");
        set("owner_name", "地堤");
        set_temp("owner", "titi");
        set_temp("owner_name", "地堤");
        ::setup();
}
