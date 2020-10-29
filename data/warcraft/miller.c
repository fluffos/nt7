// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大头娃娃[2;37;0m[2;37;0m", ({"datou"}));        
        set("gender", "女性");                
        set("long", "xxx[2;37;0m
它是米勒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "miller");
        set("owner_name", "米勒");
        set_temp("owner", "miller");
        set_temp("owner_name", "米勒");
        ::setup();
}
