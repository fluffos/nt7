// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("绵工[2;37;0m[2;37;0m", ({"atk"}));        
        set("gender", "男性");                
        set("long", "绵工[2;37;0m
它是临兵的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tka");
        set("owner_name", "临兵");
        set_temp("owner", "tka");
        set_temp("owner_name", "临兵");
        ::setup();
}
