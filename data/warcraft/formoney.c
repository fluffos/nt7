// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡睡[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "睡睡[2;37;0m
它是为了钱的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "formoney");
        set("owner_name", "为了钱");
        set_temp("owner", "formoney");
        set_temp("owner_name", "为了钱");
        ::setup();
}
