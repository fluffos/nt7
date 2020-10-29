// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("山地[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "女性");                
        set("long", "           [2;37;0m
它是龙一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "longa");
        set("owner_name", "龙一");
        set_temp("owner", "longa");
        set_temp("owner_name", "龙一");
        ::setup();
}
