// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"dddd"}));        
        set("gender", "男性");                
        set("long", "魔幻兽[2;37;0m
它是来了也的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kankan");
        set("owner_name", "来了也");
        set_temp("owner", "kankan");
        set_temp("owner_name", "来了也");
        ::setup();
}
