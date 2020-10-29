// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[2;37;0m[2;37;0m", ({"pys"}));        
        set("gender", "男性");                
        set("long", "spy[2;37;0m
它是的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "spy");
        set("owner_name", "");
        set_temp("owner", "spy");
        set_temp("owner_name", "");
        ::setup();
}
