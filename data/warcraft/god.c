// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("浴火重生[2;37;0m[2;37;0m", ({"sleepbag_"}));        
        set("gender", "男性");                
        set("long", "浴火重生[2;37;0m
它是天神的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "god");
        set("owner_name", "天神");
        set_temp("owner", "god");
        set_temp("owner_name", "天神");
        ::setup();
}
