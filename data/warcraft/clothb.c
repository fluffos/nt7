// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m太古凶兽[2;37;0m[2;37;0m", ({"clothblong"}));        
        set("gender", "男性");                
        set("long", "万恶[2;37;0m
它是锦衣卫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "clothb");
        set("owner_name", "锦衣卫");
        set_temp("owner", "clothb");
        set_temp("owner_name", "锦衣卫");
        ::setup();
}
