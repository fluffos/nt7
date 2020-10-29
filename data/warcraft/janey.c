// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哺哺[2;37;0m[2;37;0m", ({"bubu"}));        
        set("gender", "男性");                
        set("long", "哺哺[2;37;0m
它是胜光奇兵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "janey");
        set("owner_name", "胜光奇兵");
        set_temp("owner", "janey");
        set_temp("owner_name", "胜光奇兵");
        ::setup();
}
