// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙龙[2;37;0m[2;37;0m", ({"xlong"}));        
        set("gender", "男性");                
        set("long", "@@@@[2;37;0m
它是苍穹无悔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iceleon");
        set("owner_name", "苍穹无悔");
        set_temp("owner", "iceleon");
        set_temp("owner_name", "苍穹无悔");
        ::setup();
}
