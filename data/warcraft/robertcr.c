// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m闹闹[2;37;0m[2;37;0m", ({"benben"}));        
        set("gender", "男性");                
        set("long", "闹闹[2;37;0m
它是澄东的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "robertcr");
        set("owner_name", "澄东");
        set_temp("owner", "robertcr");
        set_temp("owner_name", "澄东");
        ::setup();
}
