// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("孤寒[2;37;0m[2;37;0m", ({"guhan"}));        
        set("gender", "男性");                
        set("long", "像狗[2;37;0m
它是期望的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hnmdsa");
        set("owner_name", "期望");
        set_temp("owner", "hnmdsa");
        set_temp("owner_name", "期望");
        ::setup();
}
