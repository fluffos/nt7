// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"pet"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是赵灵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bya");
        set("owner_name", "赵灵");
        set_temp("owner", "bya");
        set_temp("owner_name", "赵灵");
        ::setup();
}
