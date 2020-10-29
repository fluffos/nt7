// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙龙[2;37;0m[2;37;0m", ({"ttt"}));        
        set("gender", "男性");                
        set("long", "龙龙[2;37;0m
它是通不痛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tbt");
        set("owner_name", "通不痛");
        set_temp("owner", "tbt");
        set_temp("owner_name", "通不痛");
        ::setup();
}
