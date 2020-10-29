// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神仙龙[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "神仙龙[2;37;0m
它是龙龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "longlong");
        set("owner_name", "龙龙");
        set_temp("owner", "longlong");
        set_temp("owner_name", "龙龙");
        ::setup();
}
