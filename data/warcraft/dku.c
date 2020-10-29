// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m芦苇[2;37;0m[2;37;0m", ({"dkuu"}));        
        set("gender", "男性");                
        set("long", "$HIW$芦苇[2;37;0m
它是枯木的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dku");
        set("owner_name", "枯木");
        set_temp("owner", "dku");
        set_temp("owner_name", "枯木");
        ::setup();
}
