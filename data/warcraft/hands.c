// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m掌魔[2;37;0m[2;37;0m", ({"handshands"}));        
        set("gender", "男性");                
        set("long", "$HIR$掌魔[2;37;0m
它是魔掌的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hands");
        set("owner_name", "魔掌");
        set_temp("owner", "hands");
        set_temp("owner_name", "魔掌");
        ::setup();
}
