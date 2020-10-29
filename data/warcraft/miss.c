// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神驹[2;37;0m[2;37;0m", ({"longe"}));        
        set("gender", "男性");                
        set("long", "神驹[2;37;0m
它是东门官人的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "miss");
        set("owner_name", "东门官人");
        set_temp("owner", "miss");
        set_temp("owner_name", "东门官人");
        ::setup();
}
