// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"mycar"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是工人一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gonga");
        set("owner_name", "工人一");
        set_temp("owner", "gonga");
        set_temp("owner_name", "工人一");
        ::setup();
}
