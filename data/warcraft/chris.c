// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "勇气、智慧与美丽于一身的强大生物。[2;37;0m
它是海程的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chris");
        set("owner_name", "海程");
        set_temp("owner", "chris");
        set_temp("owner_name", "海程");
        ::setup();
}
