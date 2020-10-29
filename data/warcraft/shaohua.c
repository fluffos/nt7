// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m璃[2;37;0m[2;37;0m", ({"qinli"}));        
        set("gender", "男性");                
        set("long", "璃[2;37;0m
它是韶华白首的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shaohua");
        set("owner_name", "韶华白首");
        set_temp("owner", "shaohua");
        set_temp("owner_name", "韶华白首");
        ::setup();
}
