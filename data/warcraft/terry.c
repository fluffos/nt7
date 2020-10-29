// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m龙龙[2;37;0m[2;37;0m", ({"lone"}));        
        set("gender", "男性");                
        set("long", "龙龙降世，白龙天下[2;37;0m
它是龙的烦恼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "terry");
        set("owner_name", "龙的烦恼");
        set_temp("owner", "terry");
        set_temp("owner_name", "龙的烦恼");
        ::setup();
}
