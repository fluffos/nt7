// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("笨笨[2;37;0m[2;37;0m", ({"leeee"}));        
        set("gender", "男性");                
        set("long", "胖乎乎[2;37;0m
它是李天保的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "leee");
        set("owner_name", "李天保");
        set_temp("owner", "leee");
        set_temp("owner_name", "李天保");
        ::setup();
}
