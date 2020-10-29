// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啪啪啪[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "砰砰砰[2;37;0m
它是东风三号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "workb");
        set("owner_name", "东风三号");
        set_temp("owner", "workb");
        set_temp("owner_name", "东风三号");
        ::setup();
}
