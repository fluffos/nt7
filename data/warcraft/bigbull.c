// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("母龙[2;37;0m[2;37;0m", ({"muu"}));        
        set("gender", "女性");                
        set("long", "一只发情期的母龙[2;37;0m
它是大牛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bigbull");
        set("owner_name", "大牛");
        set_temp("owner", "bigbull");
        set_temp("owner_name", "大牛");
        ::setup();
}
