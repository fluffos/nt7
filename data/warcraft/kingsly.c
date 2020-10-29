// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大日[2;37;0m[2;37;0m", ({"kingslya"}));        
        set("gender", "男性");                
        set("long", "大日[2;37;0m
它是散散一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kingsly");
        set("owner_name", "散散一");
        set_temp("owner", "kingsly");
        set_temp("owner_name", "散散一");
        ::setup();
}
