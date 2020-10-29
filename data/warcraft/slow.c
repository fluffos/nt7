// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m蜗牛[2;37;0m[2;37;0m", ({"mom"}));        
        set("gender", "男性");                
        set("long", "急速蜗牛[2;37;0m
它是从容不破的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "slow");
        set("owner_name", "从容不破");
        set_temp("owner", "slow");
        set_temp("owner_name", "从容不破");
        ::setup();
}
