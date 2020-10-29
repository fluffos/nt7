// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大龙[2;37;0m[2;37;0m", ({"dalong"}));        
        set("gender", "男性");                
        set("long", "大龙[2;37;0m
它是张四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lbinc");
        set("owner_name", "张四");
        set_temp("owner", "lbinc");
        set_temp("owner_name", "张四");
        ::setup();
}
