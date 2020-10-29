// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qil"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是消魂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ran");
        set("owner_name", "消魂");
        set_temp("owner", "ran");
        set_temp("owner_name", "消魂");
        ::setup();
}
