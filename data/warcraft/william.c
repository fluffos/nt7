// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("萧麟[2;37;0m[2;37;0m", ({"will"}));        
        set("gender", "男性");                
        set("long", "威猛雄壮的小马[2;37;0m
它是萧易的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "william");
        set("owner_name", "萧易");
        set_temp("owner", "william");
        set_temp("owner_name", "萧易");
        ::setup();
}
