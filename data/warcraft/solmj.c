// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小伙子[2;37;0m[2;37;0m", ({"mjid"}));        
        set("gender", "女性");                
        set("long", "小伙子[2;37;0m
它是拓锋的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "solmj");
        set("owner_name", "拓锋");
        set_temp("owner", "solmj");
        set_temp("owner_name", "拓锋");
        ::setup();
}
