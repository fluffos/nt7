// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m蹦蹦[2;37;0m[2;37;0m", ({"beng"}));        
        set("gender", "男性");                
        set("long", "蹦蹦龙。[2;37;0m
它是包打听的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jojogb");
        set("owner_name", "包打听");
        set_temp("owner", "jojogb");
        set_temp("owner_name", "包打听");
        ::setup();
}
