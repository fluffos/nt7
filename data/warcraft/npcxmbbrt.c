// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"west"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是陶涛奋的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "npcxmbbrt");
        set("owner_name", "陶涛奋");
        set_temp("owner", "npcxmbbrt");
        set_temp("owner_name", "陶涛奋");
        ::setup();
}
