// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("威龙[2;37;0m[2;37;0m", ({"brother"}));        
        set("gender", "男性");                
        set("long", "威龙在天[2;37;0m
它是悠云苍天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "faraway");
        set("owner_name", "悠云苍天");
        set_temp("owner", "faraway");
        set_temp("owner_name", "悠云苍天");
        ::setup();
}
