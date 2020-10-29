// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[36m青龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是丁铛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ddang");
        set("owner_name", "丁铛");
        set_temp("owner", "ddang");
        set_temp("owner_name", "丁铛");
        ::setup();
}
