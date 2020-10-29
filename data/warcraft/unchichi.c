// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m一[1;33m闪[1;36m闪[2;37;0m[2;37;0m", ({"flashs"}));        
        set("gender", "女性");                
        set("long", "闪闪龙[2;37;0m
它是依韵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "unchichi");
        set("owner_name", "依韵");
        set_temp("owner", "unchichi");
        set_temp("owner_name", "依韵");
        ::setup();
}
