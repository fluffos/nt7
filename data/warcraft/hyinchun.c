// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贾宝玉[2;37;0m[2;37;0m", ({"jbaoyu"}));        
        set("gender", "男性");                
        set("long", "贾宝玉[2;37;0m
它是迎春的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hyinchun");
        set("owner_name", "迎春");
        set_temp("owner", "hyinchun");
        set_temp("owner_name", "迎春");
        ::setup();
}
