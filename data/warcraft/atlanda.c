// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("舞之精灵[2;37;0m[2;37;0m", ({"cathrine"}));        
        set("gender", "男性");                
        set("long", "舞之精灵[2;37;0m
它是北之舞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "atlanda");
        set("owner_name", "北之舞");
        set_temp("owner", "atlanda");
        set_temp("owner_name", "北之舞");
        ::setup();
}
