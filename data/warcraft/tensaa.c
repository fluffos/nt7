// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青眼白龙[2;37;0m[2;37;0m", ({"icq"}));        
        set("gender", "女性");                
        set("long", "我好可怜哪...青光眼和白内障[2;37;0m
它是天煞孤星的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tensaa");
        set("owner_name", "天煞孤星");
        set_temp("owner", "tensaa");
        set_temp("owner_name", "天煞孤星");
        ::setup();
}
