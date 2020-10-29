// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m泡泡[2;37;0m[2;37;0m", ({"paopao"}));        
        set("gender", "女性");                
        set("long", "$MAG$泡泡[2;37;0m
它是陌上千绝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "demigod");
        set("owner_name", "陌上千绝");
        set_temp("owner", "demigod");
        set_temp("owner_name", "陌上千绝");
        ::setup();
}
