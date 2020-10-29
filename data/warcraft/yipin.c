// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("欧系[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "        [2;37;0m
它是一品武士的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yipin");
        set("owner_name", "一品武士");
        set_temp("owner", "yipin");
        set_temp("owner_name", "一品武士");
        ::setup();
}
