// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m胖[1;32m青龙[2;37;0m[2;37;0m", ({"pql"}));        
        set("gender", "男性");                
        set("long", "吃多了的青龙[2;37;0m
它是王一小的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cxh");
        set("owner_name", "王一小");
        set_temp("owner", "cxh");
        set_temp("owner_name", "王一小");
        ::setup();
}
