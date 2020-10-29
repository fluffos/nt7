// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[34m魔幻兽[2;37;0m[2;37;0m", ({"feee"}));        
        set("gender", "男性");                
        set("long", "魔幻兽[2;37;0m
它是一般角色的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fee");
        set("owner_name", "一般角色");
        set_temp("owner", "fee");
        set_temp("owner_name", "一般角色");
        ::setup();
}
