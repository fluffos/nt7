// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m涯[2;37;0m[2;37;0m", ({"ttff"}));        
        set("gender", "男性");                
        set("long", "梓昱的伴生宠物。[2;37;0m
它是梓昱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fftt");
        set("owner_name", "梓昱");
        set_temp("owner", "fftt");
        set_temp("owner_name", "梓昱");
        ::setup();
}
