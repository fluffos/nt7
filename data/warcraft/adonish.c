// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m烤肉马[2;37;0m[2;37;0m", ({"horseb"}));        
        set("gender", "男性");                
        set("long", "烤肉马[2;37;0m
它是阿多八的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "adonish");
        set("owner_name", "阿多八");
        set_temp("owner", "adonish");
        set_temp("owner_name", "阿多八");
        ::setup();
}
