// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青龙[2;37;0m[2;37;0m", ({"ala"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是撸啊撸的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lal");
        set("owner_name", "撸啊撸");
        set_temp("owner", "lal");
        set_temp("owner_name", "撸啊撸");
        ::setup();
}
