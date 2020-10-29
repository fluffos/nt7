// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泷泽萝拉[1;37m[2;37;0m[2;37;0m", ({"feiji"}));        
        set("gender", "男性");                
        set("long", "泷泽萝拉[2;37;0m
它是萧十一郎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "superjl");
        set("owner_name", "萧十一郎");
        set_temp("owner", "superjl");
        set_temp("owner_name", "萧十一郎");
        ::setup();
}
