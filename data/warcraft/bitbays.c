// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("霸王龙[2;37;0m[2;37;0m", ({"dargon"}));        
        set("gender", "男性");                
        set("long", "最厉害的龙[2;37;0m
它是寒雨良的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bitbays");
        set("owner_name", "寒雨良");
        set_temp("owner", "bitbays");
        set_temp("owner_name", "寒雨良");
        ::setup();
}
