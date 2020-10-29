// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("从一飞翔[2;37;0m[2;37;0m", ({"forceaa"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是内力从六的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "forceliu");
        set("owner_name", "内力从六");
        set_temp("owner", "forceliu");
        set_temp("owner_name", "内力从六");
        ::setup();
}
