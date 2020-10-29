// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青龙[2;37;0m[2;37;0m", ({"spk"}));        
        set("gender", "女性");                
        set("long", "finish[2;37;0m
它是天诛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sunpk");
        set("owner_name", "天诛");
        set_temp("owner", "sunpk");
        set_temp("owner_name", "天诛");
        ::setup();
}
