// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽兑换券[2;37;0m[2;37;0m", ({"coem"}));        
        set("gender", "男性");                
        set("long", "魔幻兽兑换券[2;37;0m
它是周额的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chem");
        set("owner_name", "周额");
        set_temp("owner", "chem");
        set_temp("owner_name", "周额");
        ::setup();
}
