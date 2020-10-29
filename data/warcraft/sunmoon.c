// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("昏天暗地[2;37;0m[2;37;0m", ({"smoon"}));        
        set("gender", "男性");                
        set("long", "啾啾挤挤[2;37;0m
它是日月重光的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sunmoon");
        set("owner_name", "日月重光");
        set_temp("owner", "sunmoon");
        set_temp("owner_name", "日月重光");
        ::setup();
}
