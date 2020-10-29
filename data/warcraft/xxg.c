// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爆乳娃[2;37;0m[2;37;0m", ({"xxglong"}));        
        set("gender", "男性");                
        set("long", "佣兵[2;37;0m
它是比索地的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xxg");
        set("owner_name", "比索地");
        set_temp("owner", "xxg");
        set_temp("owner_name", "比索地");
        ::setup();
}
