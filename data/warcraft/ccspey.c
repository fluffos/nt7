// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m风尘[2;37;0m[2;37;0m", ({"ccss"}));        
        set("gender", "男性");                
        set("long", "$HIR$风尘[2;37;0m
它是南无的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ccspey");
        set("owner_name", "南无");
        set_temp("owner", "ccspey");
        set_temp("owner_name", "南无");
        ::setup();
}
