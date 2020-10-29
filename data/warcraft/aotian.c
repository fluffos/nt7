// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青龙[2;37;0m[2;37;0m", ({"mjt"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是苦穷的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "aotian");
        set("owner_name", "苦穷");
        set_temp("owner", "aotian");
        set_temp("owner_name", "苦穷");
        ::setup();
}
