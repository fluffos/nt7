// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("框框[2;37;0m[2;37;0m", ({"kuangkuang"}));        
        set("gender", "男性");                
        set("long", "框框[2;37;0m
它是冷恶的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lenge");
        set("owner_name", "冷恶");
        set_temp("owner", "lenge");
        set_temp("owner_name", "冷恶");
        ::setup();
}
