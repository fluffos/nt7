// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"goldeee"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是金龙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldee");
        set("owner_name", "金龙");
        set_temp("owner", "goldee");
        set_temp("owner_name", "金龙");
        ::setup();
}
