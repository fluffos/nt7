// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大笨蛋[2;37;0m[2;37;0m", ({"girlioi"}));        
        set("gender", "男性");                
        set("long", "大笨蛋[2;37;0m
它是陶太狼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ttao");
        set("owner_name", "陶太狼");
        set_temp("owner", "ttao");
        set_temp("owner_name", "陶太狼");
        ::setup();
}
