// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啊粗大[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "啊粗大[2;37;0m
它是奥术这些的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zxc");
        set("owner_name", "奥术这些");
        set_temp("owner", "zxc");
        set_temp("owner_name", "奥术这些");
        ::setup();
}
