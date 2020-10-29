// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"fkka"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是耐色的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "nka");
        set("owner_name", "耐色");
        set_temp("owner", "nka");
        set_temp("owner_name", "耐色");
        ::setup();
}
