// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("驯鹿[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "驯鹿[2;37;0m
它是九剑孤独的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hstguiji");
        set("owner_name", "九剑孤独");
        set_temp("owner", "hstguiji");
        set_temp("owner_name", "九剑孤独");
        ::setup();
}
