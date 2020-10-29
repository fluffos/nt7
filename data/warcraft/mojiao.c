// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m魔魂[2;37;0m[2;37;0m", ({"hun"}));        
        set("gender", "男性");                
        set("long", "这是魔神的魂魄。[2;37;0m
它是魔教的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mojiao");
        set("owner_name", "魔教");
        set_temp("owner", "mojiao");
        set_temp("owner_name", "魔教");
        ::setup();
}
