// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m风[2;37;0m[1;31m驰[1;33m电[1;35m掣[2;37;0m[2;37;0m", ({"windy"}));        
        set("gender", "男性");                
        set("long", "风驰电掣[2;37;0m
它是风萧萧的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wind");
        set("owner_name", "风萧萧");
        set_temp("owner", "wind");
        set_temp("owner_name", "风萧萧");
        ::setup();
}
