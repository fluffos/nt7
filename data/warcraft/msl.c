// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m朱雀[2;37;0m[2;37;0m", ({"msls"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是马三力的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "msl");
        set("owner_name", "马三力");
        set_temp("owner", "msl");
        set_temp("owner_name", "马三力");
        ::setup();
}
