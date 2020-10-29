// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("酷比特[2;37;0m[2;37;0m", ({"zoox"}));        
        set("gender", "男性");                
        set("long", "酷比特[2;37;0m
它是模工幻影的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tina");
        set("owner_name", "模工幻影");
        set_temp("owner", "tina");
        set_temp("owner_name", "模工幻影");
        ::setup();
}
