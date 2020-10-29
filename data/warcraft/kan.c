// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("娜娜南岸[2;37;0m[2;37;0m", ({"ooot"}));        
        set("gender", "男性");                
        set("long", "娜娜南岸[2;37;0m
它是大大的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kan");
        set("owner_name", "大大");
        set_temp("owner", "kan");
        set_temp("owner_name", "大大");
        ::setup();
}
