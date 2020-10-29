// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m指兽[2;37;0m[2;37;0m", ({"zhib"}));        
        set("gender", "男性");                
        set("long", "$HIR$指兽[2;37;0m
它是魔指的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zhi");
        set("owner_name", "魔指");
        set_temp("owner", "zhi");
        set_temp("owner_name", "魔指");
        ::setup();
}
