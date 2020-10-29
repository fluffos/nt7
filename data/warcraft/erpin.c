// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("顺路快递[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "           [2;37;0m
它是二品武士的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "erpin");
        set("owner_name", "二品武士");
        set_temp("owner", "erpin");
        set_temp("owner_name", "二品武士");
        ::setup();
}
